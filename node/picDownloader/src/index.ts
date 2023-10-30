import * as picDLib from "./picDLib";

// TODO: theme: get as script params
//const theme:string = "rejto";
const theme:string = "rahan";
const max = 99; // TODO: break if folder not found!

const folderNamePDF: string = "hu." + theme + ".kepregeny";

// TODO: create options object instead of a lot of parameter!
function downloadNextImage(index: number, folderName: string, absFNs: Array<string>, onEnd: (fn: string) => void) {
    const sindex: string = index.toString().padStart(2, "0");
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
            onEnd("");
          }
      });
}

function downloadNextImageSet(imageSetNr: number): Promise<any> {
  const folderName = "r" + imageSetNr;
  const absFNs: Array<string> = [];
  picDLib.mkdir("_dwnld_" + theme + "_" + folderName);

  // TODO: use async/await
  const p: Promise<any> = new Promise((resolve: (value: any) => void, reject: (reason?: any) => void) => {

    const onEnd = (fn: string) : void => {
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

function doDownload(imageSetNr: number) {
  downloadNextImageSet(imageSetNr).then((opts: any) => {
    if (imageSetNr < max) {
      doDownload(imageSetNr + 1);
    }
  })
  .catch((err: any) => {
      console.error("error in doDownload " + imageSetNr + ". Possibly sequence ended.", err);
  });
}

picDLib.mkdir(folderNamePDF);
doDownload(1);
