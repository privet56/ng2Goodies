;
const $import2exportAnalyzer = (() => { //IIFE

    const import_analyse = (sImportJson, eTaResults) => {
        eTaResults.value = "";
        const importPayload = $sync.analyse(sImportJson, eTaResults);

        // $sync.out(eTaResults, " \n###### - Import-specific Analyses: ######\n");
        // if (initial) -> do all id-references reference existing entities?

        return importPayload;
    };

    const export_analyse = (sImportJson, sExportJson, eTaResults) => {
        eTaResults.value = "";
        const exportPayload = $sync.analyse(sExportJson, eTaResults);
        if (!exportPayload) return;

        $sync.out(eTaResults, " \n###### - Export-specific Analyses: ######\n");

        const importPayload = JSON.parse(sImportJson)['result']['payload'];

        countExportElesInImport(importPayload, exportPayload, 'employee.calendar.VacationRequest', eTaResults);
    };

    function countExportElesInImport(importPayload, exportPayload, eleName/*eg. 'employee.calendar.VacationRequest'*/, eTaResults) {
        const importVacReqs = importPayload ? $sync.getGrandChildren(importPayload[eleName]) : [];
        const exportVacReqs = exportPayload ? $sync.getGrandChildren(exportPayload[eleName]) : [];

        if (!importVacReqs || !exportVacReqs) {
            return;
        }
        let isInImportCount = 0;
        let isInImportCountAndChanged = 0;
        for (let i = 0; i < exportVacReqs.length; i++) {

            const id = exportVacReqs[i]['id'];
            const importVacReq = $sync.isIdInArray(importVacReqs, id, eTaResults);
            if (importVacReq) {
                isInImportCount++;
                const status = $sync.getChange(importVacReq, exportVacReqs[i], 'status');
                const syncStatus = $sync.getChange(importVacReq, exportVacReqs[i], 'syncStatus');
                if (status || syncStatus) {
                    isInImportCountAndChanged++;
                }
                $sync.out(eTaResults, "VacReq(" + id + "):" + status + syncStatus);
            }
        }
        $sync.out(eTaResults, "Exported #VacationRequest found in import: " + isInImportCount + " isInImportCountAndChanged: " + isInImportCountAndChanged);
    }

    return { // the exported public interface
        import_analyse: import_analyse,
        export_analyse: export_analyse
    }
})($sync); // '$sync' DI: inject object with additional functions; architectural pattern: prefer composition to inheritance
