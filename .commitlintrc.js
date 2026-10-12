module.exports = {
  extends: ["@commitlint/config-conventional"],
  plugins: [
    {
      rules: {
        // custom rule: enforce scope formats
        // - for `retry`: scope = <problem_id>,<result_code> (e.g. retry(0001,WA))
        // - for `solve` and `skip`: scope = <problem_id> (e.g. solve(0042))
        "scope-format": (parsed) => {
          const t = parsed.type;
          const s = parsed.scope || "";
          if (t === "retry") {
            const ok = /^\d{4},(WA|TLE|OLE|MLE|RE|PE|CE|CREDIT)$/.test(s);
            return [
              ok,
              "For type 'retry' the scope must be '<problem_id>,<result_code>' (e.g. retry(0001,WA)) with code one of WA,TLE,OLE,MLE,RE,PE,CE,CREDIT",
            ];
          }
          if (t === "solve" || t === "skip") {
            const ok = /^\d{4}$/.test(s);
            return [
              ok,
              "For type '" + t + "' the scope must be a 4-digit problem id (e.g. " + t + "(0042))",
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
