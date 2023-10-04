# setup ts project
npm install typescript --save-dev
npm install @types/node --save-dev
npx tsc --init --rootDir src --outDir build --esModuleInterop --resolveJsonModule --lib es6 --module commonjs --allowJs true --noImplicitAny true
npm install --save-dev ts-node nodemon
npm install --save-dev rimraf

# project specific libs
npm install axios
npm install image-downloader

# start command
npm run start:dev
