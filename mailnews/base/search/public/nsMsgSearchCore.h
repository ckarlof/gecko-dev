/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1999 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#ifndef _nsMsgSearchCore_H_
#define _nsMsgSearchCore_H_

#include "MailNewsTypes.h"
#include "nsString2.h"

class nsMsgDatabase;
class nsIMsgFolder;

typedef enum
{
    nsMsgSearchScopeMailFolder,
    nsMsgSearchScopeNewsgroup,
    nsMsgSearchScopeLdapDirectory,
    nsMsgSearchScopeOfflineNewsgroup,
	nsMsgSearchScopeAllSearchableGroups
} nsMsgSearchScopeAttribute;

typedef enum
{
    nsMsgSearchAttribSubject = 0,	/* mail and news */
    nsMsgSearchAttribSender,   
    nsMsgSearchAttribBody,	
    nsMsgSearchAttribDate,	

    nsMsgSearchAttribPriority,	    /* mail only */
    nsMsgSearchAttribMsgStatus,	
    nsMsgSearchAttribTo,
    nsMsgSearchAttribCC,
    nsMsgSearchAttribToOrCC,

    nsMsgSearchAttribCommonName,   /* LDAP only */
    nsMsgSearchAttrib822Address,	
    nsMsgSearchAttribPhoneNumber,
    nsMsgSearchAttribOrganization,
    nsMsgSearchAttribOrgUnit,
    nsMsgSearchAttribLocality,
    nsMsgSearchAttribStreetAddress,
    nsMsgSearchAttribSize,
    nsMsgSearchAttribAnyText,      /* any header or body */
	nsMsgSearchAttribKeywords,

    nsMsgSearchAttribDistinguishedName, /* LDAP result elem only */
    nsMsgSearchAttribObjectClass,       
    nsMsgSearchAttribJpegFile,

    nsMsgSearchAttribLocation,          /* result list only */
    nsMsgSearchAttribMessageKey,        /* message result elems */

	nsMsgSearchAttribAgeInDays,    /* for purging old news articles */

	nsMsgSearchAttribGivenName,    /* for sorting LDAP results */
	nsMsgSearchAttribSurname, 

	nsMsgSearchAttribFolderInfo,	/* for "view thread context" from result */

	nsMsgSearchAttribCustom1,		/* custom LDAP attributes */
	nsMsgSearchAttribCustom2,
	nsMsgSearchAttribCustom3,
	nsMsgSearchAttribCustom4,
	nsMsgSearchAttribCustom5,

	nsMsgSearchAttribMessageId, 
	/* the following are LDAP specific attributes */
	nsMsgSearchAttribCarlicense,
	nsMsgSearchAttribBusinessCategory,
	nsMsgSearchAttribDepartmentNumber,
	nsMsgSearchAttribDescription,
	nsMsgSearchAttribEmployeeType,
	nsMsgSearchAttribFaxNumber,
	nsMsgSearchAttribManager,
	nsMsgSearchAttribPostalAddress,
	nsMsgSearchAttribPostalCode,
	nsMsgSearchAttribSecretary,
	nsMsgSearchAttribTitle,
	nsMsgSearchAttribNickname,
	nsMsgSearchAttribHomePhone,
	nsMsgSearchAttribPager,
	nsMsgSearchAttribCellular,

	nsMsgSearchAttribOtherHeader,  /* for mail and news. MUST ALWAYS BE LAST attribute since we can have an arbitrary # of these...*/
    kNumMsgSearchNumAttributes      /* must be last attribute */
} nsMsgSearchAttribute;

/* NB: If you add elements to this enum, add only to the end, since 
 *     RULES.DAT stores enum values persistently
 */
typedef enum
{
    nsMsgSearchOpContains = 0,     /* for text attributes              */
    nsMsgSearchOpDoesntContain,
    nsMsgSearchOpIs,               /* is and isn't also apply to some non-text attrs */
    nsMsgSearchOpIsnt, 
    nsMsgSearchOpIsEmpty,

    nsMsgSearchOpIsBefore,         /* for date attributes              */
    nsMsgSearchOpIsAfter,
    
    nsMsgSearchOpIsHigherThan,     /* for priority. nsMsgSearchOpIs also applies  */
    nsMsgSearchOpIsLowerThan,

    nsMsgSearchOpBeginsWith,              
	nsMsgSearchOpEndsWith,

    nsMsgSearchOpSoundsLike,       /* for LDAP phoenetic matching      */
	nsMsgSearchOpLdapDwim,         /* Do What I Mean for simple search */

	nsMsgSearchOpIsGreaterThan,	
	nsMsgSearchOpIsLessThan,

	nsMsgSearchOpNameCompletion,   /* Name Completion operator...as the name implies =) */

    kNumMsgSearchOperators       /* must be last operator            */
} nsMsgSearchOperator;

/* FEs use this to help build the search dialog box */
typedef enum
{
    nsMsgSearchWidgetText,
    nsMsgSearchWidgetDate,
    nsMsgSearchWidgetMenu,
	nsMsgSearchWidgetInt,          /* added to account for age in days which requires an integer field */
    nsMsgSearchWidgetNone
} nsMsgSearchValueWidget;

/* Used to specify type of search to be performed */
typedef enum
{
	nsMsgSearchNone,
	nsMsgSearchRootDSE,
	nsMsgSearchNormal,
	nsMsgSearchLdapVLV,
	nsMsgSearchNameCompletion
} nsMsgSearchType;

typedef enum {nsMsgSearchBooleanOR, nsMsgSearchBooleanAND} nsMsgSearchBooleanOp;

/* Use this to specify the value of a search term */
typedef struct nsMsgSearchValue
{
    nsMsgSearchAttribute attribute;
    union
    {
        char *string;
        nsMsgPriority priority;
        time_t date;
        PRUint32 msgStatus; /* see MSG_FLAG in msgcom.h */
        PRUint32 size;
        nsMsgKey key;
		PRUint32 age; /* in days */
		nsIMsgFolder *folder;
    } u;
} nsMsgSearchValue;

struct nsMsgScopeTerm;
struct nsMsgResultElement;
struct nsMsgDIRServer;

//---------------------------------------------------------------------------
// nsMsgSearchTerm specifies one criterion, e.g. name contains phil
//---------------------------------------------------------------------------

class nsMsgSearchTerm
{
public:
	nsMsgSearchTerm();
	nsMsgSearchTerm (nsMsgSearchAttribute, nsMsgSearchOperator, nsMsgSearchValue *, PRBool, char * arbitraryHeader); // the bool is true if AND, FALSE if OR
	nsMsgSearchTerm (nsMsgSearchAttribute, nsMsgSearchOperator, nsMsgSearchValue *, nsMsgSearchBooleanOp, char * arbitraryHeader);

	virtual ~nsMsgSearchTerm ();

	void StripQuotedPrintable (unsigned char*);
	int32 GetNextIMAPOfflineMsgLine (char * buf, int bufferSize, int msgOffset, nsIMessage * msg, nsMsgDatabase * db);


	nsresult MatchBody (nsMsgScopeTerm*, PRUint32 offset, PRUint32 length, PRInt16 csid, nsIMsgFolder * msg, nsMsgDatabase * db);
	nsresult MatchArbitraryHeader (nsMsgScopeTerm *,PRUint32 offset, PRUint32 length, PRInt16 csid, nsIMsgFolder * msg, nsMsgDatabase *db,
											char * headers, /* NULL terminated header list for msgs being filtered. Ignored unless ForFilters */
											PRUint32 headersSize, /* size of the NULL terminated list of headers */
											PRBool ForFilters /* true if we are filtering */);
	nsresult MatchString (const char *, PRInt16 csid, PRBool body = FALSE);
	nsresult MatchDate (time_t);
	nsresult MatchStatus (PRUint32);
	nsresult MatchPriority (nsMsgPriority);
	nsresult MatchSize (PRUint32);
	nsresult MatchRfc822String(const char *, int16 csid);
	nsresult MatchAge (time_t);

	nsresult EnStreamNew (char **, PRInt16 *length);
	nsresult DeStream (char *, PRInt16 length);
	nsresult DeStreamNew (char *, PRInt16 length);

	nsresult GetLocalTimes (time_t, time_t, struct tm &, struct tm &);

	PRBool IsBooleanOpAND() { return m_booleanOp == nsMsgSearchBooleanAND ? PR_TRUE : PR_FALSE;}
	nsMsgSearchBooleanOp GetBooleanOp() {return m_booleanOp;}
	char * GetArbitraryHeader() {return m_arbitraryHeader;}

	static char *	EscapeQuotesInStr(const char *str);
	PRBool MatchAllBeforeDeciding ();
	nsMsgSearchAttribute m_attribute;
	nsMsgSearchOperator m_operator;
	nsMsgSearchValue m_value;
	nsMsgSearchBooleanOp m_booleanOp;  // boolean operator to be applied to this search term and the search term which precedes it.
	char * m_arbitraryHeader;         // user specified string for the name of the arbitrary header to be used in the search
									  // only has a value when m_attribute = attribOtherHeader!!!!
protected:
	nsresult		OutputValue(nsString2 &outputStr);
	nsMsgSearchAttribute ParseAttribute(char *inStream);
	nsMsgSearchOperator	ParseOperator(char *inStream);
	nsresult		ParseValue(char *inStream);
	virtual PRUint32 GetExpectedMagic ();
	static PRUint32 m_expectedMagic;
};

inline PRUint32 nsMsgSearchTerm::GetExpectedMagic ()
{
	return m_expectedMagic; 
}


/* Use this to help build menus in the search dialog. See APIs below */
#define kMsgSearchMenuLength 64
typedef struct nsMsgSearchMenuItem 
{
    int16 attrib;
    char name[kMsgSearchMenuLength];
    PRBool isEnabled;
} nsMsgSearchMenuItem;


class nsMsgSearchTermArray : public nsVoidArray
{
public:
	nsMsgSearchTerm *ElementAt(PRUint32 i) const { return (nsMsgSearchTerm*) nsVoidArray::ElementAt(i); }
};

class nsMsgSearchValueArray : public nsVoidArray
{
public:
	nsMsgSearchValue *ElementAt(PRUint32 i) const { return (nsMsgSearchValue*) nsVoidArray::ElementAt(i); }
};

class nsMsgScopeTermArray : public nsVoidArray
{
public:
	nsMsgScopeTerm *ElementAt(PRUint32 i) const { return (nsMsgScopeTerm*) nsVoidArray::ElementAt(i); }
};



#endif // _nsMsgSearchCore_H_
