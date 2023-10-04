const fs = require('fs');
const Axios = require('axios')

const download = require('image-downloader');

const folderName = "r7";

if (!fs.existsSync("_dwnld_"+folderName)) {
    fs.mkdirSync("_dwnld_"+folderName);
}

function downloadImage(url: string, filepath: string) {
    return download.image({
       url,
       dest: filepath 
    });
}

const min: number = 1;
const max: number = 66;

for(let index: number = min; index <= max; index++) {
    const sindex: string = index.toString().padStart(2, "0");
    const url = `http://dydudu.hu/kepreg/rejto/${folderName}/k${sindex}.jpg`;
    const absFN = `${__dirname}/../_dwnld_${folderName}/k${sindex}.jpg`;
    const asyncDownload = downloadImage(url, absFN);
    // TODO: await asyncDownload;
}

// TODO: pdf from downloaded pic

// export {}; // to allow await
