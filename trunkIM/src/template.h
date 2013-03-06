
class TempalteMap;

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>
#include <Qfile>
#include <QTextStream>
#include <QMap>
#include "main.h"
#include "Elise.h"

//extern QString skinPath;

class TemplateMap {
private:
	QUrl			qurlSkinPath;
	QString			qstrSkinPath;
	bool			inited;
	bool			filesInOut;
	bool			urlInOut;
public:
	TemplateMap();
	TemplateMap(TemplateMap* other);
	~TemplateMap();

	QUrl			getTemplateUrl();
	QString*		getTemplatePath();
	QString			getRealTemplatePath();
	//-- We are setting qurlSkinPath in setTemplatePath.
	void			setTemplatePath(QString* path);
	void			setTemplatePath(wchar_t pszPath[MAX_PATH]);

	bool			isTemplateInited() {return inited;};
	//bool			isGroupsSup() {return groupsSupported;};
	bool			isFilesInOut() {return filesInOut;};
	bool			isURLInOut() {return urlInOut;};

	QMap<QString, QString> templateMap;
	int				loadTemplate();

	static QMap<QString, QRegExp> templateBBCodes;
	static void		loadBBCodes();	

};

#endif // TEMPLATE_H