# setup commands
npm install typescript --save-dev
npm install @types/node --save-dev
npx tsc --init --rootDir src --outDir build --esModuleInterop --resolveJsonModule --lib es6 --module commonjs --allowJs true --noImplicitAny true
npm install --save-dev ts-node nodemon
npm install --save-dev rimraf

# start command
npm run start:dev
