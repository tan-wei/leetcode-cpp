module.exports = {
  extends: ["@commitlint/config-conventional"],
  plugins: [
    {
      rules: {
        // custom rule: enforce scope formats
        // - for `retry`: require a result code scope:
        // WA,TLE,OLE,MLE,RE,PE,CE,CREDIT (e.g. retry(WA))
        // - for `solve` and `skip`: no special validation
        "scope-format": (parsed) => {
          const t = parsed.type;
          const s = parsed.scope || "";
          if (t === "retry") {
            const ok = /^(WA|TLE|OLE|MLE|RE|PE|CE|CREDIT)$/.test(s);
            return [
              ok,
              "For type 'retry' the scope must be one of WA,TLE,OLE,MLE,RE,PE,CE,CREDIT (e.g. retry(WA))",
            ];
          }
          return [true];
        },
      },
    },
  ],
  rules: {
    "header-max-length": [1, "always", 50],
    "body-max-line-length": [1, "always", 72],
    // allowed commit types (prefixes)
    "type-enum": [
      2,
      "always",
      [
        "refactor",
        "docs",
        "test",
        "revert",
        "perf",
        "build",
        "solve",
        "chore",
        "fix",
        "ci",
        "skip",
        "retry",
        "style",
      ],
    ],
    // activate custom scope-format plugin rule
    "scope-format": [2, "always"],
    // disable subject-case enforcement so both "Do it" and "do it" are accepted
    "subject-case": [0, "always"],
  },
};
