#include <QAxObject>
#include <QFile>
#include <QMessageBox>
#include "qmsoffice.h"
#include "windows.h"

#define wdCollapseEnd 0

qmsoffice::qmsoffice(QObject *parent, helpers* helper) : QObject(parent)
{
    this->m_phelper = helper;
    CoInitializeEx( 0, COINIT_APARTMENTTHREADED);
}
int qmsoffice::embedpics(QAxObject* pDoc, QAxObject* pContentWithPics, QAxObject* pDocContent)
{
    int iCount = pContentWithPics->property("Count").toInt();
    if (iCount < 1)return 0;

    int iLinksBreaked = 0;

    for(int i=0; i <= iCount;i++)
    {
        QVariant item(i);
        QAxObject* pItem = pContentWithPics->querySubObject("Item(const QVariant&)", item);
        if(!pItem)continue;
        connect(pItem, SIGNAL( exception ( int, const QString&, const QString&, const QString& ) ), this, SLOT( SlotComException( int, const QString&, const QString&, const QString& ) ) );

        QAxObject* pLinkFormat = querySubObject(pItem,"LinkFormat");
        pLinkFormat->dynamicCall("BreakLink()");
        iLinksBreaked++;
    }
    return iLinksBreaked;
}
void qmsoffice::embedpics(QAxObject* pDoc, QAxObject* pDocContent)
{
    {
        QAxObject* pEmbedable = querySubObject(pDoc,"Fields");
        if(pEmbedable && (embedpics(pDoc, pEmbedable, pDocContent) > 0))
            pDoc->dynamicCall("UndoClear()");
    }
    {
        QAxObject* pShapes = querySubObject(pDoc,"Shapes");
        if(pShapes && (embedpics(pDoc, pShapes, pDocContent) > 0))
            pDoc->dynamicCall("UndoClear()");
    }
    {
        QAxObject* pInlineShapes = querySubObject(pDoc,"InlineShapes");
        if(pInlineShapes && (embedpics(pDoc, pInlineShapes, pDocContent) > 0))
            pDoc->dynamicCall("UndoClear()");
    }
}

QAxObject* qmsoffice::querySubObject(QAxObject* pO, QString sSubObject)
{
    if(!pO || helpers::str_isempty(sSubObject, true))
    {
        log("qmso:querySubObject\tERR:!pO sSubObject:"+sSubObject);return 0;
    }
    QAxObject* r = pO->querySubObject(sSubObject);
    if(!r)
    {
        log("qmso:querySubObject\tERR:!r in pO("+QString(pO->name())+") sSubObject:"+sSubObject);return 0;
    }
    connect(r, SIGNAL( exception ( int, const QString&, const QString&, const QString& ) ), this, SLOT( SlotComException( int, const QString&, const QString&, const QString& ) ) );
    return r;
}

bool qmsoffice::openAsNew(QString sAbsFNhtml, QString sAbsFNdot)
{
    QAxObject* word = new QAxObject("Word.Application",0);
    QAxObject* pDocuments = querySubObject(word,"Documents");
    if(!pDocuments)
    {
        log("qmso:openAsNew\tERR:!pDocuments");return false;
    }

    connect(word, SIGNAL( exception ( int, const QString&, const QString&, const QString& ) ), this, SLOT( SlotComException( int, const QString&, const QString&, const QString& ) ) );

    QAxObject* pDoc = 0;
    {
        QVariant filename(sAbsFNhtml);
        QVariant confirmconversions(false);
        QVariant readonly(true);
        QVariant addtorecentfiles(false);
        QVariant passworddocument("");
        QVariant passwordtemplate("");
        QVariant revert(false);
        pDoc = pDocuments->querySubObject("Open(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)", filename,confirmconversions, readonly, addtorecentfiles, passworddocument, passwordtemplate, revert);
    }
    if(!pDoc)
    {
        log("qmso:openAsNew\tERR:!pAddedDoc");return false;
    }
    connect(pDoc, SIGNAL( exception ( int, const QString&, const QString&, const QString& ) ), this, SLOT( SlotComException( int, const QString&, const QString&, const QString& ) ) );
    QAxObject* pDocAll = querySubObject(pDoc,"Content()");
    pDocAll->dynamicCall("Select()");
    pDocAll->dynamicCall("Copy()");
    pDoc->dynamicCall("Close()");

    QAxObject* pNewDoc = 0;
    QAxObject* pNewDocAll =  0;
    if(!helpers::str_isempty(sAbsFNdot, true) && QFile::exists(sAbsFNdot))
    {
        sAbsFNdot=sAbsFNdot.replace('/','\\');
        QVariant filename(sAbsFNdot);
        QVariant confirmconversions(false);
        QVariant readonly(true);
        QVariant addtorecentfiles(false);
        QVariant passworddocument("");
        QVariant passwordtemplate("");
        QVariant revert(false);

        pNewDoc      = pDocuments->querySubObject("Add (const QVariant&,const QVariant&)",filename, confirmconversions);
        //pNewDoc     = pDocuments->querySubObject("Open(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)", filename,confirmconversions, readonly, addtorecentfiles, passworddocument, passwordtemplate, revert);
        pNewDocAll  = querySubObject(pNewDoc, "Content()");
        {
            //QAxObject* Range = ActiveDocument->querySubObject("Range()");
            //querySubObject("InsertAfter(QString)","mytext")

            QAxObject* pNewDocFind = querySubObject(pNewDocAll, "Find()");
            pNewDocFind->dynamicCall("ClearFormatting()");
            QList<QVariant> params;
            params.operator << (QVariant("%CONTENT%"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant(true));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant(""));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            params.operator << (QVariant("0"));
            pNewDocFind->dynamicCall("Execute(const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,"
                              "const QVariant&,const QVariant&,const QVariant&)",
                              params);

            pNewDocAll->dynamicCall("Paste()");

            /*
            QVariant v1_replacemode(0);    //(wdReplaceNone = 0, wdReplaceOne = 1, wdReplaceAll = 2)
            QVariant v2_replacewith();
            QVariant v3_replaceformat();
            QVariant v4_replacewrap();
            QVariant v5_replaceforward(true);
            QVariant v6_replacematchAllWordForms(true);
            QVariant v7_replacematchSoundsLike(false);
            QVariant v8_replacematchWildCards(false);
            QVariant v9_replacematchWholeWord(true);
            QVariant v10_replacematchCaseSens(true);
            QVariant v11_text2find("%CONTENT%");
            QList<QVariant> pars;

            int ii=0;
            pars.append(v1_replacemode);
            ii++;
            pars.append(v2_replacewith);
            ii++;
            pars.append(v3_replaceformat);
            ii++;
            pars.append(v4_replacewrap);
            pars.append(v5_replaceforward);
            pars.append(v6_replacematchAllWordForms);
            pars.append(v7_replacematchSoundsLike);
            pars.append(v8_replacematchWildCards);
            pars.append(v9_replacematchWholeWord);
            pars.append(v10_replacematchCaseSens);
            pars.append(v11_text2find);

            QAxObject* pNewDocFind = pNewDocAll->querySubObject("Find(const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&,const QVariant&)",pars);
            */
        }
        //pNewDocFind->dynamicCall(".Text = \"const QVariant&\"",QVariant("%CONTENT%"));
    }
    else
    {
        pNewDoc      = querySubObject(pDocuments,"Add (void)");
        pNewDocAll   = querySubObject(pNewDoc, "Content()");
        pNewDocAll->dynamicCall("Select()");
        QAxObject* pSelection = querySubObject(word, "Selection()");
        pSelection->dynamicCall("ClearFormatting()");
        //QVariant vCollapse(wdCollapseEnd);
        //pSelection->dynamicCall("Collapse(const QVariant&)",vCollapse);
        //pSelection->dynamicCall("Paste()");

        //??? oWord.Selection.PasteSpecial Link:=False, DataType:=1, DisplayAsIcon:=False
        pNewDocAll->dynamicCall("Paste()");
    }

    embedpics(pNewDoc, pNewDocAll);
    word->setProperty( "Visible", true );
    return true;


    //goto END: Set objSelection = objWord.Selection;   objSelection.EndKey wdStory, wdMove
    //documents->dynamicCall("Add (void)");     //adds a new doc

    /*
    AxObject* WordApplication=new QAxObject("Word.Application"); // ?????? ????????? ? MSWord
    QAxObject* WordDocuments = WordApplication->querySubObject( "Documents()" ); // ??????? ?????????? ? ??? ?????????? "????????? ???????? ??????????":
    WordDocuments->querySubObject( "Add()" ); // ?????? ????? ????????
    // ?????????? ??????????
    QAxObject* Grammatic = WordApplication->querySubObject("Options()");
    Grammatic->setProperty("CheckSpellingAsYouType(bool)", false); // ?????????? ??????????
    QAxObject* ActiveDocument = WordApplication->querySubObject("ActiveDocument()");
    QAxObject* Range = ActiveDocument->querySubObject("Range()");
    // ???????? ???????
    QAxObject* Tables = ActiveDocument->querySubObject("Tables()");
    QAxObject* NewTable = Tables->querySubObject("Add(Range, NumRows, NumColumns, DefaultTableBehavior, AutoFitBehavior)", ActiveDocument->dynamicCall("Range()"), 4, 4, 1, 1);
    // ?????? ?????? ? ??????
    QAxObject* Cell = NewTable->querySubObject("Cell(Row, Column)", 1,1);
    QAxObject* CellRange = Cell->querySubObject("Range()");
    CellRange->dynamicCall("InsertAfter(Text)", "??? ?????? 1:1");
    */
    /*
    //Open newDocName
    QVariant filename(newDocName);
    QVariant confirmconversions(false);
    QVariant readonly(false);
    QVariant addtorecentfiles(false);
    QVariant passworddocument("");
    QVariant passwordtemplate("");
    QVariant revert(false);
    QAxObject* pDoc = my_docs->querySubObject("Open(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)", filename,confirmconversions, readonly, addtorecentfiles, passworddocument, passwordtemplate,	revert);

    if(!pDoc)
    {
        log("qmso:openAsNew\tERR:!pDoc");return false;
    }

    //Pull out active document object
    QAxObject* active_doc = my_app->querySubObject("ActiveDocument");

    QVariant newFileName(fileNameString);
    QVariant fileFormat(10); //Saving as filtered html
    QVariant LockComments(false);
    QVariant Password("");
    QVariant recent(true);
    QVariant writePassword("");
    QVariant ReadOnlyRecommended(false);

    active_doc->querySubObject("SaveAs(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)",    newFileName, fileFormat, LockComments, Password, recent, writePassword, ReadOnlyRecommended);
    */
    /*
    QVariantList params;
    params << m_docs.at( i ) << true << false << false << "" << "" << false << false << "" << "" << 0 << false << true << 0 << true << false;
    QAxObject* pDoc = pDocuments->querySubObject( "OpenNoRepairDialog (QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&)", params );
    if(! pDoc )
    {
        return false;
    }
    connect( pDoc, SIGNAL( exception ( int, const QString&, const QString&, const QString& ) ), this, SLOT( SlotComException( int, const QString&, const QString&, const QString& ) ) );

    pDoc->dynamicCall( "PrintOut(boolean)", false );
    pDoc->dynamicCall( "Close(boolean)", false );

    QString lastPrinter = pWord->property( "ActivePrinter" ).toString();
    pWord->setProperty( "Visible", true );

    delete pDocuments;
    delete pWord;
    */
}

void qmsoffice::SlotComException(int i, const QString& s1, const QString& s2, const QString& s3)
{
    log("COM EXCP:("+QString::number(i)+")"+s1+" <> "+s2+" <> "+s3);
}
void qmsoffice::log(QString s, int iLogLevel)
{
    if (this->m_phelper)
        this->m_phelper->log(s, iLogLevel, this->m_phelper->m_pApp, this->m_phelper->m_pLogTarget, true);
}
