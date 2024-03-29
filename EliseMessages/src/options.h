/*
Elise Messages Plugin for Miranda IM

*/

class TemplateMap;
class Options;
class SingleOptions;

#ifndef OPTIONS_H
#define OPTIONS_H

#include "main.h"
#include "template.h"
#include "../resource.h"

extern const QString cqstrNotSet;
extern const QUrl cqurlNotSet;
extern const unsigned char cNotSet;

typedef struct {
	unsigned char	cBBCodes;
	unsigned char	cURLParse;
	unsigned char	cMessageGrouping;
	unsigned char	cShowAvatar;
	unsigned char	cShowTime;
	unsigned char	cShowSeconds;
	unsigned char	cShowDate;
	unsigned char	cWordDate;
	unsigned char	cRelativeTime;
	unsigned char	cShowSmileys;
	wchar_t			pszPath[MAX_PATH];
} SAVEOPTIONS;

//-- This class is used to store one exemplar of settings
//-- (i.e. settings for one contact or protocol... or general default settings).
class SingleOptions {
private:
	
	//-- Note:	0 is disabled
	//--		1 is enabled
	//--		2 is not set (use cNotSet constant)
	unsigned char	cBBCodes;
	unsigned char	cURLParse;
	unsigned char	cMessageGrouping;
	unsigned char	cShowAvatar;
	unsigned char	cShowTime;
	unsigned char	cShowSeconds;
	unsigned char	cShowDate;
	unsigned char	cWordDate;
	unsigned char	cRelativeTime;
	unsigned char	cShowSmileys;
	//bool			bJQueryUse;
public:
	TemplateMap*	currentTemplate;

	SingleOptions();
	SingleOptions(SingleOptions* other);
	SingleOptions::SingleOptions(HANDLE hContact);
	~SingleOptions();

	//-- Getters
	inline unsigned char	isBBCodes() {return cBBCodes;};
	inline unsigned char	isURLParse() {return cURLParse;};
	inline unsigned char	isMessageGrouping() {return cMessageGrouping;};
	inline unsigned char	isShowAvatar() {return cShowAvatar;};
	inline unsigned char	isShowTime() {return cShowTime;};
	inline unsigned char	isShowSeconds() {return cShowSeconds;};
	inline unsigned char	isShowDate() {return cShowDate;};
	inline unsigned char	isWordDate() {return cWordDate;};
	inline unsigned char	isRelativeTime() {return cRelativeTime;};
	inline unsigned char	isShowSmileys() {return cShowSmileys;};
	//inline bool				isJQueryUsed() { return bJQueryUse; }

	//-- Setters
	inline void			setBBcodes(unsigned char val) {cBBCodes = val;};
	inline void			setURLParse(unsigned char val) {cURLParse = val;};
	inline void			setMessageGrouping(unsigned char val) {cMessageGrouping = val;};
	inline void			setShowAvatar(unsigned char val) {cShowAvatar = val;};
	inline void			setShowTime(unsigned char val) {cShowTime = val;};
	inline void			setShowSeconds(unsigned char val) {cShowSeconds = val;};
	inline void			setShowDate(unsigned char val) {cShowDate = val;};
	inline void			setWordDate(unsigned char val) {cWordDate = val;};
	inline void			setRelativeTime(unsigned char val) {cRelativeTime = val;};
	inline void			setShowSmileys(unsigned char val) {cShowSmileys = val;};
	//inline void			setJQueryUsed(bool used) { bJQueryUse = used; };
}; //SingleOptions

class Options {
private:
	//static int initialized;
	//static int changed;
	static QMap<QString, SingleOptions*>	settings;
	static QMap<QString, SAVEOPTIONS*>*	settingsToSave;
	inline static void		findSettingsInMap(HANDLE hContact, QString& qsUIN, QString& qsProto)
	{
		char* szUINIn = NULL;
		char* szProto = NULL;
		getUINs(hContact, szUINIn);
		szProto =  Utils::dupString((char*)CallService(MS_PROTO_GETCONTACTBASEPROTO, (WPARAM) hContact, 0));
		qsUIN = QString::fromAscii(szUINIn);
		qsProto = QString::fromAscii(szProto);
		if (szUINIn!=NULL) delete szUINIn;
		if (szProto!=NULL) delete szProto;
	};
	//-- Decode byte value
	inline static UINT		updateCheckBox(unsigned char val)
	{
		switch (val) {			
		case (2):   //-- cNotSet = 0
			return BST_INDETERMINATE;
			break;
		case (1):
			return BST_CHECKED;
			break;
		case (0):
			return BST_UNCHECKED;
			break;
		default:
			return BST_INDETERMINATE;
			break;
		}
	};
	//-- Encode byte value
	inline static unsigned char readCheckBox(UINT val)
	{
		switch (val) {
		case (BST_INDETERMINATE):
			return cNotSet;
			break;
		case (BST_CHECKED):
			return 1;
			break;
		case (BST_UNCHECKED):
			return 0;
			break;
		default:
			return cNotSet;
			break;
		}
	};
public:
	static QString*	currentTab;
	static void		saveSettings(HWND hwnd);
	static int		initOptionsPage(WPARAM wParam, LPARAM lParam);
	//static int		modulesLoaded(WPARAM wParam, LPARAM lParam);
	//static void MarkInitialized(int i);
	//static void ApplyChanges(int i);
	//static void MarkChanges(int i, HWND hWnd);
	static void		destroyTempParts();
	static bool		BrowseFile(HWND hwndDlg, wchar_t* filter, wchar_t* defExt,  wchar_t* path, int maxLen);
	static void		getUINs(HANDLE hContact, char* &uinIn, char* &uinOut);
	static void		getUINs(HANDLE hContact, char* &uinIn);
	static HANDLE	getRealContact(HANDLE hContact);
	static char*	getProto(HANDLE hContact);
	static char*	getProto(const char* proto, HANDLE hContact);
	static HANDLE	wndToContact(HWND hwnd);
	static void		buildProtocolList(HWND hwnd);
	static void		updateProtocolSettings(HWND hwndDlg, wchar_t proto[MAX_PATH]);
	static void		saveSingleSettings(HWND hwndDlg, QString qsProto, HANDLE hContact, SAVEOPTIONS* opt);
	static int		loadSingleSettings(char* szProto, HANDLE hContact);
	static int		prepareToSave(HWND hwndDlg);
	static int		updateSettingsInMap(QString qsProto, SAVEOPTIONS* opt);

	//-- This function return pointer to the valid TemplateMap for contact
	//-- or NULL if no one was found
	static TemplateMap*		isTemplateInited(HANDLE hContact);

	//-- This functions translate call to map members
	static unsigned char	isBBCodes(HANDLE hContact);
	static unsigned char	isURLParse(HANDLE hContact);
	static unsigned char	isMessageGrouping(HANDLE hContact);
	static unsigned char	isShowAvatar(HANDLE hContact);
	static unsigned char	isShowTime(HANDLE hContact);
	static unsigned char	isShowSeconds(HANDLE hContact);
	static unsigned char	isShowDate(HANDLE hContact);
	static unsigned char	isWordDate(HANDLE hContact);
	static unsigned char	isRelativeTime(HANDLE hContact);
	static unsigned char	isShowSmileys(HANDLE hContact);
	static bool				isJQueryUsed(HANDLE hContact);

	static int		initOptions();
	inline static QMap<QString, SingleOptions*>*	getSettingsMap() {return &settings;};
}; //Options

#endif // OPTIONS_H
