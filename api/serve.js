const fs = require("fs");
const path = require("path");

// Repo root: this file lives in <root>/api, so go one level up.
const ROOT = path.join(__dirname, "..");

// Things we never want to expose in the browser.
const HIDDEN = new Set([".git", ".vercel", "node_modules", "api"]);

const MIME = {
  ".html": "text/html; charset=utf-8",
  ".css": "text/css; charset=utf-8",
  ".js": "text/javascript; charset=utf-8",
  ".json": "application/json; charset=utf-8",
  ".md": "text/plain; charset=utf-8",
  ".c": "text/plain; charset=utf-8",
  ".h": "text/plain; charset=utf-8",
  ".txt": "text/plain; charset=utf-8",
  ".pdf": "application/pdf",
  ".png": "image/png",
  ".jpg": "image/jpeg",
  ".jpeg": "image/jpeg",
  ".gif": "image/gif",
  ".svg": "image/svg+xml",
  ".docx":
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
};

function esc(s) {
  return String(s)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;");
}

function fmtSize(bytes) {
  if (bytes < 1024) return bytes + " B";
  if (bytes < 1024 * 1024) return (bytes / 1024).toFixed(1) + " KB";
  return (bytes / (1024 * 1024)).toFixed(1) + " MB";
}

// Resolve a user-supplied relative path safely inside ROOT.
function resolveSafe(rel) {
  const clean = decodeURIComponent(rel || "").replace(/^\/+/, "");
  const target = path.normalize(path.join(ROOT, clean));
  if (target !== ROOT && !target.startsWith(ROOT + path.sep)) return null;
  return { target, rel: clean.replace(/\\/g, "/") };
}

function listing(target, rel) {
  const entries = fs
    .readdirSync(target, { withFileTypes: true })
    .filter((e) => !HIDDEN.has(e.name))
    .sort((a, b) => {
      if (a.isDirectory() !== b.isDirectory()) return a.isDirectory() ? -1 : 1;
      return a.name.localeCompare(b.name, undefined, { numeric: true });
    });

  const crumbs = ["/"].concat(rel ? rel.split("/") : []);
  let acc = "";
  const crumbHtml = crumbs
    .map((c, i) => {
      if (i === 0) return '<a href="/">root</a>';
      acc += (acc ? "/" : "") + c;
      return ` / <a href="/${esc(acc)}">${esc(c)}</a>`;
    })
    .join("");

  const rows = entries
    .map((e) => {
      const childRel = (rel ? rel + "/" : "") + e.name;
      const href = "/" + childRel.split("/").map(encodeURIComponent).join("/");
      const icon = e.isDirectory() ? "📁" : "📄";
      const name = esc(e.name) + (e.isDirectory() ? "/" : "");
      let size = "";
      if (!e.isDirectory()) {
        try {
          size = fmtSize(fs.statSync(path.join(target, e.name)).size);
        } catch (_) {}
      }
      return `<tr><td>${icon} <a href="${href}">${name}</a></td><td class="s">${size}</td></tr>`;
    })
    .join("");

  return `<!doctype html><html><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>${esc(rel || "Graph-Theory")}</title>
<style>
:root{color-scheme:light dark}
body{font:15px/1.5 ui-monospace,SFMono-Regular,Menlo,Consolas,monospace;max-width:820px;margin:40px auto;padding:0 16px}
h1{font-size:18px;margin:0 0 4px}.bc{color:#888;margin-bottom:20px;word-break:break-all}
a{color:#3b82f6;text-decoration:none}a:hover{text-decoration:underline}
table{width:100%;border-collapse:collapse}td{padding:6px 8px;border-bottom:1px solid #8884}
td.s{text-align:right;color:#888;white-space:nowrap}
</style></head><body>
<h1>Graph-Theory file server</h1>
<div class="bc">${crumbHtml}</div>
<table>${rows || '<tr><td>(empty)</td><td></td></tr>'}</table>
</body></html>`;
}

module.exports = (req, res) => {
  const raw = Array.isArray(req.query.path) ? req.query.path[0] : req.query.path;
  const r = resolveSafe(raw);
  if (!r) {
    res.statusCode = 403;
    res.end("Forbidden");
    return;
  }

  let stat;
  try {
    stat = fs.statSync(r.target);
  } catch (_) {
    res.statusCode = 404;
    res.end("Not found: " + esc(r.rel));
    return;
  }

  if (stat.isDirectory()) {
    res.setHeader("Content-Type", "text/html; charset=utf-8");
    res.end(listing(r.target, r.rel));
    return;
  }

  const ext = path.extname(r.target).toLowerCase();
  const type = MIME[ext] || "application/octet-stream";
  res.setHeader("Content-Type", type);
  res.setHeader(
    "Content-Disposition",
    `inline; filename="${path.basename(r.target)}"`
  );
  res.end(fs.readFileSync(r.target));
};
