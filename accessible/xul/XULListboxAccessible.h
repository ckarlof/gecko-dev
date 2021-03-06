/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_a11y_XULListboxAccessible_h__
#define mozilla_a11y_XULListboxAccessible_h__

#include "BaseAccessibles.h"
#include "TableAccessible.h"
#include "TableCellAccessible.h"
#include "xpcAccessibleTable.h"
#include "xpcAccessibleTableCell.h"
#include "XULMenuAccessible.h"
#include "XULSelectControlAccessible.h"

class nsIWeakReference;

namespace mozilla {
namespace a11y {

/**
 * XULColumAccessible are accessible for list and tree columns elements
 * (xul:treecols and xul:listcols).
 */
class XULColumAccessible : public AccessibleWrap
{
public:
  XULColumAccessible(nsIContent* aContent, DocAccessible* aDoc);

  // Accessible
  virtual a11y::role NativeRole() MOZ_OVERRIDE;
  virtual uint64_t NativeState() MOZ_OVERRIDE;
};

/**
 * XULColumnItemAccessible are accessibles for list and tree column elements
 * (xul:listcol and xul:treecol).
 */
class XULColumnItemAccessible : public LeafAccessible
{
public:
  XULColumnItemAccessible(nsIContent* aContent, DocAccessible* aDoc);

  // Accessible
  virtual a11y::role NativeRole() MOZ_OVERRIDE;
  virtual uint64_t NativeState() MOZ_OVERRIDE;

  // ActionAccessible
  virtual uint8_t ActionCount() MOZ_OVERRIDE;
  virtual void ActionNameAt(uint8_t aIndex, nsAString& aName) MOZ_OVERRIDE;
  virtual bool DoAction(uint8_t aIndex) MOZ_OVERRIDE;

  enum { eAction_Click = 0 };
};

/*
 * A class the represents the XUL Listbox widget.
 */
class XULListboxAccessible : public XULSelectControlAccessible,
                             public TableAccessible
{
public:
  XULListboxAccessible(nsIContent* aContent, DocAccessible* aDoc);

  // TableAccessible
  virtual uint32_t ColCount() MOZ_OVERRIDE;
  virtual uint32_t RowCount() MOZ_OVERRIDE;
  virtual Accessible* CellAt(uint32_t aRowIndex, uint32_t aColumnIndex) MOZ_OVERRIDE;
  virtual bool IsColSelected(uint32_t aColIdx) MOZ_OVERRIDE;
  virtual bool IsRowSelected(uint32_t aRowIdx) MOZ_OVERRIDE;
  virtual bool IsCellSelected(uint32_t aRowIdx, uint32_t aColIdx) MOZ_OVERRIDE;
  virtual uint32_t SelectedCellCount() MOZ_OVERRIDE;
  virtual uint32_t SelectedColCount() MOZ_OVERRIDE;
  virtual uint32_t SelectedRowCount() MOZ_OVERRIDE;
  virtual void SelectedCells(nsTArray<Accessible*>* aCells) MOZ_OVERRIDE;
  virtual void SelectedCellIndices(nsTArray<uint32_t>* aCells) MOZ_OVERRIDE;
  virtual void SelectedColIndices(nsTArray<uint32_t>* aCols) MOZ_OVERRIDE;
  virtual void SelectedRowIndices(nsTArray<uint32_t>* aRows) MOZ_OVERRIDE;
  virtual void SelectRow(uint32_t aRowIdx) MOZ_OVERRIDE;
  virtual void UnselectRow(uint32_t aRowIdx) MOZ_OVERRIDE;
  virtual Accessible* AsAccessible() MOZ_OVERRIDE { return this; }

  // Accessible
  virtual void Value(nsString& aValue) MOZ_OVERRIDE;
  virtual TableAccessible* AsTable() MOZ_OVERRIDE { return this; }
  virtual a11y::role NativeRole() MOZ_OVERRIDE;
  virtual uint64_t NativeState() MOZ_OVERRIDE;

  // Widgets
  virtual bool IsWidget() const MOZ_OVERRIDE;
  virtual bool IsActiveWidget() const MOZ_OVERRIDE;
  virtual bool AreItemsOperable() const MOZ_OVERRIDE;

  virtual Accessible* ContainerWidget() const MOZ_OVERRIDE;

protected:
  virtual ~XULListboxAccessible() {}

  bool IsMulticolumn() { return ColCount() > 1; }
};

/**
  * Listitems -- used in listboxes
  */
class XULListitemAccessible : public XULMenuitemAccessible
{
public:
  enum { eAction_Click = 0 };

  NS_DECL_ISUPPORTS_INHERITED

  XULListitemAccessible(nsIContent* aContent, DocAccessible* aDoc);

  // Accessible
  virtual void Description(nsString& aDesc) MOZ_OVERRIDE;
  virtual a11y::role NativeRole() MOZ_OVERRIDE;
  virtual uint64_t NativeState() MOZ_OVERRIDE;
  virtual uint64_t NativeInteractiveState() const MOZ_OVERRIDE;
  virtual bool CanHaveAnonChildren() MOZ_OVERRIDE;

  // Actions
  virtual void ActionNameAt(uint8_t index, nsAString& aName) MOZ_OVERRIDE;

  // Widgets
  virtual Accessible* ContainerWidget() const MOZ_OVERRIDE;

protected:
  virtual ~XULListitemAccessible();

  // Accessible
  virtual ENameValueFlag NativeName(nsString& aName) MOZ_OVERRIDE;

  // XULListitemAccessible

  /**
   * Return listbox accessible for the listitem.
   */
  Accessible* GetListAccessible() const;

private:
  bool mIsCheckbox;
};

/**
 * Class represents xul:listcell.
 */
class XULListCellAccessible : public HyperTextAccessibleWrap,
                              public TableCellAccessible
{
public:
  XULListCellAccessible(nsIContent* aContent, DocAccessible* aDoc);

  // nsISupports
  NS_DECL_ISUPPORTS_INHERITED

  // Accessible
  virtual TableCellAccessible* AsTableCell() MOZ_OVERRIDE { return this; }
  virtual already_AddRefed<nsIPersistentProperties> NativeAttributes() MOZ_OVERRIDE;
  virtual a11y::role NativeRole() MOZ_OVERRIDE;

  // TableCellAccessible
  virtual TableAccessible* Table() const MOZ_OVERRIDE;
  virtual uint32_t ColIdx() const MOZ_OVERRIDE;
  virtual uint32_t RowIdx() const MOZ_OVERRIDE;
  virtual void ColHeaderCells(nsTArray<Accessible*>* aHeaderCells) MOZ_OVERRIDE;
  virtual bool Selected() MOZ_OVERRIDE;

protected:
  virtual ~XULListCellAccessible() {}
};

} // namespace a11y
} // namespace mozilla

#endif
