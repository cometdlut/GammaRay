/*
  sourcelocation.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "sourcelocation.h"

using namespace GammaRay;

SourceLocation::SourceLocation()
    : m_line(-1)
    , m_column(-1)
{
}

SourceLocation::SourceLocation(const QUrl &url, int line, int column)
    : m_url(url)
    , m_line(line)
    , m_column(column)
{
}

SourceLocation::~SourceLocation()
{
}

bool SourceLocation::isValid() const
{
    return m_url.isValid();
}

QUrl SourceLocation::url() const
{
    return m_url;
}

void SourceLocation::setUrl(const QUrl &url)
{
    m_url = url;
}

int SourceLocation::line() const
{
    return m_line;
}

void SourceLocation::setLine(int line)
{
    m_line = line;
}

int SourceLocation::column() const
{
    return m_column;
}

void SourceLocation::setColumn(int column)
{
    m_column = column;
}

QString SourceLocation::displayString() const
{
    if (m_url.isEmpty())
        return QString();

    QString result;

    if (m_url.isLocalFile())
        result = m_url.toLocalFile();
    else
        result = m_url.toString();

    if (m_line < 1)
        return result;

    result += QString::fromLatin1(":%1").arg(m_line);

    if (m_column >= 1)
        result += QString::fromLatin1(":%1").arg(m_column);

    return result;
}

QDataStream &GammaRay::operator<<(QDataStream &out, const SourceLocation &location)
{
    out << location.m_url;
    out << location.m_line;
    out << location.m_column;
    return out;
}

QDataStream &GammaRay::operator>>(QDataStream &in, SourceLocation &location)
{
    in >> location.m_url;
    in >> location.m_line;
    in >> location.m_column;
    return in;
}
