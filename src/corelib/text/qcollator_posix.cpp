/****************************************************************************
**
** Copyright (C) 2020 Aleix Pol Gonzalez <aleixpol@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qcollator_p.h"
#include "qstringlist.h"
#include "qstring.h"

#include <cstring>
#include <cwchar>

#ifdef __amigaos4__
namespace std {
typedef basic_string<wchar_t>    wstring;
}
#endif

QT_BEGIN_NAMESPACE

void QCollatorPrivate::init()
{
    if (!isC()) {
        if (locale != QLocale())
            qWarning("Only C and default locale supported with the posix collation implementation");
        if (caseSensitivity != Qt::CaseSensitive)
            qWarning("Case insensitive sorting unsupported in the posix collation implementation");
    }
    if (numericMode)
        qWarning("Numeric mode unsupported in the posix collation implementation");
    if (ignorePunctuation)
        qWarning("Ignoring punctuation unsupported in the posix collation implementation");
    dirty = false;
}

void QCollatorPrivate::cleanup()
{
}

static void stringToWCharArray(QVarLengthArray<wchar_t> &ret, QStringView string)
{
    ret.resize(string.length());
    int len = string.toWCharArray(ret.data());
    ret.resize(len+1);
    ret[len] = 0;
}

int QCollator::compare(QStringView s1, QStringView s2) const
{
    if (!s1.size())
        return s2.size() ? -1 : 0;
    if (!s2.size())
        return +1;

    if (d->isC())
        return s1.compare(s2, caseSensitivity());
    if (d->dirty)
        d->init();

    QVarLengthArray<wchar_t> array1, array2;
    stringToWCharArray(array1, s1);
    stringToWCharArray(array2, s2);
#ifdef __amigaos4__
    return s1.compare(s2, caseSensitivity());
#else
    return std::wcscoll(array1.constData(), array2.constData());
#endif
}

QCollatorSortKey QCollator::sortKey(const QString &string) const
{
    if (d->dirty)
        d->init();

    QVarLengthArray<wchar_t> original;
    stringToWCharArray(original, string);
    QList<wchar_t> result(original.size());
#ifndef __amigaos4__
    if (d->isC()) {
#endif
        std::copy(original.cbegin(), original.cend(), result.begin());
#ifndef __amigaos4__
    } else {
        size_t size = std::wcsxfrm(result.data(), original.constData(), string.size());
        if (size > uint(result.size())) {
            result.resize(size+1);
            size = std::wcsxfrm(result.data(), original.constData(), string.size());
        }
        result.resize(size+1);
        result[size] = 0;
    }
#endif
    return QCollatorSortKey(new QCollatorSortKeyPrivate(std::move(result)));
}

int QCollatorSortKey::compare(const QCollatorSortKey &otherKey) const
{
#ifdef __amigaos4__
    return std::wstring(d->m_key.constData()) == std::wstring(otherKey.d->m_key.constData());
#else
    return std::wcscmp(d->m_key.constData(), otherKey.d->m_key.constData());
#endif
}

QT_END_NAMESPACE
