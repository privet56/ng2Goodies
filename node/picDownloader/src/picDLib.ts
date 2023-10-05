const fs = require('fs');
const download = require('image-downloader');

function mkdir(dirName: string): void {
    if (!fs.existsSync(dirName)) {
        fs.mkdirSync(dirName);
    }    
}

function downloadImage(url: string, filepath: string) {
    return download.image({
       url,
       dest: filepath 
    });
}

module.exports = { mkdir, downloadImage };
export { mkdir, downloadImage };
