Set-Location Server
npm ci
npm run build

Set-Location ../WebClient
npm ci
Remove-Item deploy/build -Force -Recurse
npm run build
Copy-Item build/ -Destination deploy/build/ -Recurse -Force