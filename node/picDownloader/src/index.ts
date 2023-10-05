import * as picDLib from "./picDLib";

// TODO: iterate all folders: r1 to r??
const folderName = "r3";
const absFNs: Array<string> = [];

picDLib.mkdir("_dwnld_"+folderName);

function downloadNextImage(index: number, folderName: string, absFNs: Array<string>) {
    const sindex: string = index.toString().padStart(2, "0");
    const url = `http://dydudu.hu/kepreg/rejto/${folderName}/k${sindex}.jpg`;
    const absFN = `${__dirname}/../_dwnld_${folderName}/k${sindex}.jpg`;
    const asyncDownload = picDLib.downloadImage(url, absFN);
    asyncDownload.then((opts: any) => {
        absFNs.push(absFN);
        downloadNextImage(index + 1, folderName, absFNs);
      })
      .catch((err: any) => {
          console.error("error: " + err);
          picDLib.makepdf(`${__dirname}/../_dwnld_${folderName}/${folderName}.pdf`, absFNs);

      });

}

downloadNextImage(1, folderName, absFNs);
