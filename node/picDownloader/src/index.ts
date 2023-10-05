import * as picDLib from "./picDLib";

const folderName = "r3";

picDLib.mkdir("_dwnld_"+folderName);

function downloadNextImage(index: number, folderName: string) {
    const sindex: string = index.toString().padStart(2, "0");
    const url = `http://dydudu.hu/kepreg/rejto/${folderName}/k${sindex}.jpg`;
    const absFN = `${__dirname}/../_dwnld_${folderName}/k${sindex}.jpg`;
    const asyncDownload = picDLib.downloadImage(url, absFN);
    console.log('started ', url);
    asyncDownload.then((opts: any) => {
        console.log('Saved to', opts.filename);
        downloadNextImage(index + 1, folderName);
      })
      .catch((err: any) => console.error("error: " + err));

}

downloadNextImage(1, folderName);
