/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
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
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */
/* AUTO-GENERATED. DO NOT EDIT!!! */

#ifndef nsIDOMHTMLHRElement_h__
#define nsIDOMHTMLHRElement_h__

#include "nsISupports.h"
#include "nsString.h"
#include "nsIScriptContext.h"
#include "nsIDOMHTMLElement.h"


#define NS_IDOMHTMLHRELEMENT_IID \
{ 0x6f765303,  0xee43, 0x11d1, \
 { 0x9b, 0xc3, 0x00, 0x60, 0x08, 0x8c, 0xa6, 0xb3 } } 

class nsIDOMHTMLHRElement : public nsIDOMHTMLElement {
public:

  NS_IMETHOD    GetAlign(nsString& aAlign)=0;
  NS_IMETHOD    SetAlign(const nsString& aAlign)=0;

  NS_IMETHOD    GetNoShade(PRBool* aNoShade)=0;
  NS_IMETHOD    SetNoShade(PRBool aNoShade)=0;

  NS_IMETHOD    GetSize(nsString& aSize)=0;
  NS_IMETHOD    SetSize(const nsString& aSize)=0;

  NS_IMETHOD    GetWidth(nsString& aWidth)=0;
  NS_IMETHOD    SetWidth(const nsString& aWidth)=0;
};


#define NS_DECL_IDOMHTMLHRELEMENT   \
  NS_IMETHOD    GetAlign(nsString& aAlign);  \
  NS_IMETHOD    SetAlign(const nsString& aAlign);  \
  NS_IMETHOD    GetNoShade(PRBool* aNoShade);  \
  NS_IMETHOD    SetNoShade(PRBool aNoShade);  \
  NS_IMETHOD    GetSize(nsString& aSize);  \
  NS_IMETHOD    SetSize(const nsString& aSize);  \
  NS_IMETHOD    GetWidth(nsString& aWidth);  \
  NS_IMETHOD    SetWidth(const nsString& aWidth);  \



#define NS_FORWARD_IDOMHTMLHRELEMENT(superClass)  \
  NS_IMETHOD    GetAlign(nsString& aAlign) { return superClass::GetAlign(aAlign); } \
  NS_IMETHOD    SetAlign(const nsString& aAlign) { return superClass::SetAlign(aAlign); } \
  NS_IMETHOD    GetNoShade(PRBool* aNoShade) { return superClass::GetNoShade(aNoShade); } \
  NS_IMETHOD    SetNoShade(PRBool aNoShade) { return superClass::SetNoShade(aNoShade); } \
  NS_IMETHOD    GetSize(nsString& aSize) { return superClass::GetSize(aSize); } \
  NS_IMETHOD    SetSize(const nsString& aSize) { return superClass::SetSize(aSize); } \
  NS_IMETHOD    GetWidth(nsString& aWidth) { return superClass::GetWidth(aWidth); } \
  NS_IMETHOD    SetWidth(const nsString& aWidth) { return superClass::SetWidth(aWidth); } \


extern nsresult NS_InitHTMLHRElementClass(nsIScriptContext *aContext, void **aPrototype);

extern "C" NS_DOM nsresult NS_NewScriptHTMLHRElement(nsIScriptContext *aContext, nsIDOMHTMLHRElement *aSupports, nsISupports *aParent, void **aReturn);

#endif // nsIDOMHTMLHRElement_h__
