const fs = require('fs');
const download = require('image-downloader');
const imgToPDF = require('image-to-pdf')

function mkdir(dirName: string): void {
    if (!fs.existsSync(dirName)) {
        fs.mkdirSync(dirName);
    }    
}

function downloadImage(url: string, filepath: string) {
    // TODO: check if target pic already downloaded
    return download.image({
       url,
       dest: filepath 
    });
}

function makepdf(absFNPdf: string, absFNPics: Array<string>): void {
    // TODO: check if target pdf already exists.
    imgToPDF(absFNPics, imgToPDF.sizes.A4).pipe(fs.createWriteStream(absFNPdf));
    console.log("created("+absFNPics.length+"): " + absFNPdf);
}

module.exports = { mkdir, downloadImage, makepdf };
export { mkdir, downloadImage, makepdf };
