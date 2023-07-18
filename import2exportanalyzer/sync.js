;
const $sync = (() => {

    const objectConstructor = ({}).constructor;
    const analyse = (sJson, eTaResults) => {

        try {

            let json = JSON.parse(sJson);
            let payload = json['result']['payload'];
            for (let aPayloadName in payload) {

                let aPayloadValue = payload[aPayloadName];
                if (!aPayloadValue || aPayloadValue.constructor !== objectConstructor) continue;

                out(eTaResults, "" + aPayloadName + ":");
                for (let aPayloadObjMemberName in aPayloadValue) {
                    let aPayloadObjMemberValue = aPayloadValue[aPayloadObjMemberName];
                    out(eTaResults, " -> #" + aPayloadObjMemberName + ": " + aPayloadObjMemberValue.length);
                    countBy(aPayloadObjMemberValue, 'syncStatus', eTaResults);
                    countBy(aPayloadObjMemberValue, 'status', eTaResults);
                }
            }
            return payload;

        } catch (e) {
            $sync.out(eTaResults, "ERROR: " + e);
            return null;
        }
    };

    const countBy = (a, memberName, eTaResults) => {

        const counter = {};
        for (let i = 0; i < a.length; i++) {
            const memberValue = a[i][memberName];
            if (!memberValue) continue;
            counter[memberValue] = (counter[memberValue] ? counter[memberValue] + 1 : 1);
        }
        for (const memberValue in counter) {
            out(eTaResults, " ---> " + memberName + ": " + memberValue + " = " + counter[memberValue]);
        }
    }

    const eById = (id) => {
        return document.getElementById(id);
    };

    const out = (eTextArea, s) => {
        eTextArea.value += s + "\n";
    };

    const isIdInArray = (a, id, eTaResults) => {
        for (let i = 0; i < a.length; i++) {
            const oId = a[i]['id'];
            if (!oId) {
                out(eTaResults, "id:" + id + " .object has no id! " + o);
            }
            if (oId === id) {
                return a[i];
            }
        }
        return false;
    }

    const getChange = (o1, o2, memberName) => {
        return o1[memberName] === o2[memberName] ? '' : (" " + memberName + ": " + o1[memberName] + "->" + o2[memberName]);
    }

    const getGrandChildren = (o) => {
        const r = [];
        if (!o) {
            return r;
        }
        for (let e in o) {
            r.push(...o[e]);
        }
        return r;
    }

    return {
        eById: eById,
        analyse: analyse,
        isIdInArray: isIdInArray,
        out: out,
        getGrandChildren: getGrandChildren,
        countBy: countBy,
        getChange: getChange
    }
})();
