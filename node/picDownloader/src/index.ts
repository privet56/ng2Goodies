import * as picDLib from "./picDLib";

const theme:string = "rahan"; // TODO: theme: get as script params // "rejto";
const bDoPad = false;         // TODO: rejto needs padding, rahan not!

const folderNamePDF: string = "hu." + theme + ".kepregeny";

// TODO: create options object instead of a lot of parameter!
function downloadNextImage(index: number, folderName: string, absFNs: Array<string>, onEnd: (fn: string|null) => void) {
    const sindex: string = bDoPad ? index.toString().padStart(2, "0") : index.toString();
    const url = `http://dydudu.hu/kepreg/${theme}/${folderName}/k${sindex}.jpg`;
    const absFN = `${__dirname}/../_dwnld_${theme}_${folderName}/k${sindex}.jpg`;
    const asyncDownload = picDLib.downloadImage(url, absFN);
    asyncDownload.then((opts: any) => {
        absFNs.push(absFN);
        downloadNextImage(index + 1, folderName, absFNs, onEnd);
      })
      .catch((err: any) => {

          // TODO: check kind of error: 404 is expected, anything else is a real error

          if (index > 1) {
            const fn:string = `${__dirname}/../${folderNamePDF}/hu.${theme}.kepregeny.${folderName}.pdf`;
            picDLib.makepdf(fn, absFNs);
            console.error("ended downloading(i:"+index+", folder: "+folderName+", absFNs#: "+absFNs.length+"): url: "+ url);
            onEnd(fn);
          }
          else {
            console.error("error downloading(i:"+index+", folder: "+folderName+", absFNs#: "+absFNs.length+"): url: "+ url);
            onEnd(null);
          }
      });
}

function downloadNextImageSet(imageSetNr: number): Promise<any> {
  const folderName = "r" + imageSetNr;
  const absFNs: Array<string> = [];
  picDLib.mkdir("_dwnld_" + theme + "_" + folderName);

  // TODO: use async/await
  const p: Promise<any> = new Promise((resolve: (value: any) => void, reject: (reason?: any) => void) => {

    const onEnd = (fn: string|null) : void => { // TODO: better with 2 params, where first param is the error object (null if everything went well)
      if (fn) {
        resolve(fn);
      }
      else {
        reject(fn);
      }
    }
    downloadNextImage(1, folderName, absFNs, onEnd);
  });
  
  return p;
}

function doDownloadAllmageSet(imageSetNr: number) {
  downloadNextImageSet(imageSetNr).then((opts: any) => {
    if (imageSetNr < 99) { // i don't expect more than 99 imageSets within one theme
      // TODO: wait a little bit, otherwise i overload the weak web server!
      doDownloadAllmageSet(imageSetNr + 1);
    }
  })
  .catch((err: any) => {
      console.error("error in doDownloadAllmageSet " + imageSetNr + ". Possibly sequence ended.", err);
  });
}

picDLib.mkdir(folderNamePDF);
doDownloadAllmageSet(1);
