Set-Location Server
npm ci
npm run build

Set-Location ../WebClient
npm ci
Remove-Item deploy/build -Force -Recurse -ErrorAction Ignore
npm run build
Copy-Item build/ -Destination deploy/build/ -Recurse -Force