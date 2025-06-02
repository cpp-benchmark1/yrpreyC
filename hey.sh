# Lista das branches a serem criadas
branches=(
  "CWE-89-SQL-Injection"
  "CWE-94-Code-Injection"
  "CWE-787-Out-of-Buffer-Bounds-Write"
  "CWE-918-SSRF"
  "CWE-943-NoSQL-Injection"
  "pure-docker"
)

# Cria cada branch a partir da main
for branch in "${branches[@]}"; do
  git checkout main
  git pull origin main
  git checkout -b "$branch"
  git push -u origin "$branch"
done

