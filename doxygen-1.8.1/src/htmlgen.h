/******************************************************************************
 *
 * $Id: htmlgen.h,v 1.51 2001/03/19 19:27:40 root Exp $
 *
 * Copyright (C) 1997-2012 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef HTMLGEN_H
#define HTMLGEN_H

#include "qtbc.h"
#include "outputgen.h"

//#define PREFRAG_START "<div class=\"fragment\"><pre class=\"fragment\">"
//#define PREFRAG_END   "</pre></div>"
#define PREFRAG_START "<div class=\"fragment\">"
#define PREFRAG_END   "</div><!-- fragment -->"

class QFile;
class FTextStream;

class HtmlGenerator : public OutputGenerator
{
  public:
    HtmlGenerator();
    virtual ~HtmlGenerator();
    static void init();
    static void writeStyleSheetFile(QFile &f);
    static void writeHeaderFile(QFile &f, const char *cssname);
    static void writeFooterFile(QFile &f);
    static void writeTabData();
    static void writeSearchInfo(FTextStream &t,const QCString &relPath);
    static void writeSearchData(const char *dir);
    static void writeSearchPage();
    static QCString writeLogoAsString(const char *path);
    static QCString writeSplitBarAsString(const char *name,const char *relpath);
   
    void enable() 
    { if (genStack->top()) active=*genStack->top(); else active=TRUE; }
    void disable() { active=FALSE; }
    void enableIf(OutputType o)  { if (o==Html) enable();  }
    void disableIf(OutputType o) { if (o==Html) disable(); }
    void disableIfNot(OutputType o) { if (o!=Html) disable(); }
    bool isEnabled(OutputType o) { return (o==Html && active); } 
    OutputGenerator *get(OutputType o) { return (o==Html) ? this : 0; }

    void printDoc(DocNode *,const char *);

    void startFile(const char *name,const char *manName,const char *title);
    void writeFooter(const char *navPath);
    void endFile();
    void clearBuffer();
    void writeSearchInfo();

    void startIndexSection(IndexSections) {}
    void endIndexSection(IndexSections) {}
    void writePageLink(const char *,bool) {}
    void startProjectNumber();
    void endProjectNumber();
    void writeStyleInfo(int part);
    void startTitleHead(const char *);
    void endTitleHead(const char *,const char *);
    void startTitle() { t << "<div class=\"title\">"; }
    void endTitle() { t << "</div>"; }
    
    void startParagraph();
    void endParagraph();
    void writeString(const char *text);
    void startIndexListItem();
    void endIndexListItem();
    void startIndexList();
    void endIndexList();
    void startIndexKey();
    void endIndexKey();
    void startIndexValue(bool);
    void endIndexValue(const char *,bool);
    void startItemList()  { t << "<ul>"  << endl; }
    void endItemList()    { t << "</ul>" << endl; }
    void startIndexItem(const char *ref,const char *file);
    void endIndexItem(const char *ref,const char *file);
    void docify(const char *text);
    void codify(const char *text);
    void writeObjectLink(const char *ref,const char *file,
                         const char *anchor,const char *name);
    void writeCodeLink(const char *ref,const char *file,
                       const char *anchor,const char *name,
                       const char *tooltip);
    void startTextLink(const char *file,const char *anchor);
    void endTextLink();
    void startHtmlLink(const char *url);
    void endHtmlLink();
    void startTypewriter() { t << "<code>"; }
    void endTypewriter()   { t << "</code>"; }
    void startGroupHeader(int);
    void endGroupHeader(int);
    void startItemListItem() { t << "<li>"; }
    void endItemListItem() { t << "</li>\n"; }

    void startMemberSections();
    void endMemberSections();
    void startHeaderSection();
    void endHeaderSection();
    void startMemberHeader(const char *);
    void endMemberHeader();
    void startMemberSubtitle();
    void endMemberSubtitle();
    void startMemberDocList();
    void endMemberDocList();
    void startMemberList();
    void endMemberList();
    void startInlineHeader();
    void endInlineHeader();
    void startAnonTypeScope(int) {}
    void endAnonTypeScope(int) {}
    void startMemberItem(const char *anchor,int,const char *inheritId);
    void endMemberItem();
    void startMemberTemplateParams();
    void endMemberTemplateParams(const char *anchor);

    void startMemberGroupHeader(bool);
    void endMemberGroupHeader();
    void startMemberGroupDocs();
    void endMemberGroupDocs();
    void startMemberGroup();
    void endMemberGroup(bool);

    void insertMemberAlign(bool);
    void startMemberDescription(const char *anchor,const char *inheritId);
    void endMemberDescription();
    void writeInheritedSectionTitle(const char *id,const char *file,
                      const char *anchor,const char *title,const char *name);

    void writeRuler()    { t << "<hr/>"; }
    void writeAnchor(const char *,const char *name) 
                         { t << "<a name=\"" << name <<"\" id=\"" << name << "\"></a>"; }
    void startCodeFragment() { t << PREFRAG_START; }
    void endCodeFragment()   { t << PREFRAG_END; } 
    void writeLineNumber(const char *,const char *,const char *,int);
    void startCodeLine(bool);
    void endCodeLine();
    void startEmphasis() { t << "<em>";  }
    void endEmphasis()   { t << "</em>"; }
    void startBold()     { t << "<b>"; }
    void endBold()       { t << "</b>"; }
    void startDescription() { t << endl << "<dl>" << endl; }
    void endDescription()   { t << endl << "</dl>\n" << endl; }
    void startDescItem()    { t << "<dt>"; }
    void endDescItem()      { t << "</dt>"; }
    void startDescForItem() { t << "<dd>"; }
    void endDescForItem()   { t << "</dd>\n"; }
    void lineBreak(const char *style);
    void writeChar(char c);
    void startMemberDoc(const char *,const char *,const char *,const char *,bool);
    void endMemberDoc(bool); 
    void startDoxyAnchor(const char *fName,const char *manName,
                         const char *anchor,const char *name,
                         const char *args);
    void endDoxyAnchor(const char *fName,const char *anchor);
    void startCodeAnchor(const char *label);
    void endCodeAnchor();
    void writeLatexSpacing() {}
    void writeStartAnnoItem(const char *type,const char *file,
                            const char *path,const char *name);
    void writeEndAnnoItem(const char *) { t << endl; }
    void startSubsection()    { t << "<h2>"; }
    void endSubsection()      { t << "</h2>" << endl; }
    void startSubsubsection() { t << "<h3>"; }
    void endSubsubsection()   { t << "</h3>" << endl; }
    void startCenter()        { t << "<center>" << endl; }
    void endCenter()          { t << "</center>" << endl; }
    void startSmall()         { t << "<small>" << endl; }
    void endSmall()           { t << "</small>" << endl; }
    //void startDescList(SectionTypes)      { t << "<dl compact><dt><b>" << endl; }
    //void endDescList()        { t << "</dl>"; }
    void startSimpleSect(SectionTypes,const char *,const char *,const char *);
    void endSimpleSect();
    void startParamList(ParamListTypes,const char *);
    void endParamList();
    //void writeDescItem()      { t << "<dd>" << endl; }
    void startSection(const char *,const char *,SectionInfo::SectionType);
    void endSection(const char *,SectionInfo::SectionType);
    void addIndexItem(const char *,const char *);
    void startIndent();
    void endIndent();
    void writeSynopsis() {}
    void startClassDiagram();
    void endClassDiagram(const ClassDiagram &,const char *,const char *);
    void startPageRef() {}
    void endPageRef(const char *,const char *) {}
    void startQuickIndices() {}
    void endQuickIndices();
    void writeSplitBar(const char *name);
    void writeLogo();
    void writeQuickLinks(bool compact,HighlightedItem hli,const char *file);
    void startContents();
    void endContents();
    void writeNonBreakableSpace(int);
    
    void startDescTable()
    { t << "<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\">" << endl; }
    void endDescTable()
    { t << "</table>" << endl; }
    void startDescTableTitle()
    { t << "<tr><td valign=\"top\"><em>"; }
    void endDescTableTitle()
    { t << "</em>&nbsp;</td>"; }
    void startDescTableData()
    { t << "<td>" << endl; }
    void endDescTableData()
    { t << "</td></tr>" << endl; }
    
    void startDotGraph();
    void endDotGraph(const DotClassGraph &g);
    void startInclDepGraph();
    void endInclDepGraph(const DotInclDepGraph &g);
    void startGroupCollaboration();
    void endGroupCollaboration(const DotGroupCollaboration &g);
    void startCallGraph();
    void endCallGraph(const DotCallGraph &g);
    void startDirDepGraph();
    void endDirDepGraph(const DotDirDeps &g);
    void writeGraphicalHierarchy(const DotGfxHierarchyTable &g);

    void startTextBlock(bool) 
    { t << "<div class=\"textblock\">"; }
    void endTextBlock(bool) 
    { t << "</div>"; }
    void lastIndexPage() {}

    void startMemberDocPrefixItem();
    void endMemberDocPrefixItem();
    void startMemberDocName(bool);
    void endMemberDocName();
    void startParameterType(bool first,const char *key);
    void endParameterType();
    void startParameterName(bool);
    void endParameterName(bool last,bool emptyList,bool closeBracket);
    void startParameterList(bool);
    void endParameterList();

    void startConstraintList(const char *);
    void startConstraintParam();
    void endConstraintParam();
    void startConstraintType();
    void endConstraintType();
    void startConstraintDocs();
    void endConstraintDocs();
    void endConstraintList();

    void startMemberDocSimple();
    void endMemberDocSimple();
    void startInlineMemberType();
    void endInlineMemberType();
    void startInlineMemberName();
    void endInlineMemberName();
    void startInlineMemberDoc();
    void endInlineMemberDoc();

    void startFontClass(const char *s) { t << "<span class=\"" << s << "\">"; }
    void endFontClass() { t << "</span>"; }

    void startLabels();
    void writeLabel(const char *l,bool isLast);
    void endLabels();

    void writeCodeAnchor(const char *anchor) 
    { t << "<a name=\"" << anchor << "\"></a>"; }
    void linkableSymbol(int,const char *,Definition *,Definition *) {}

    //static void generateSectionImages();

  private:
    static void writePageFooter(FTextStream &t,const QCString &,const QCString &,const QCString &);
    QCString lastTitle;
    QCString lastFile;
    QCString relPath;
    void docify(const char *text,bool inHtmlComment);

    HtmlGenerator &operator=(const HtmlGenerator &g);
    HtmlGenerator(const HtmlGenerator &g);

    int col;
    int m_sectionCount;
    bool m_emptySection;
};

#endif
