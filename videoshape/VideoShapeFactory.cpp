/* This file is part of the KDE project
 * Copyright (C) 2007 Thomas Zander <zander@kde.org>
 * Copyright (C) 2007 Jan Hambrecht <jaham@gmx.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "VideoShapeFactory.h"

#include "VideoShape.h"
#include "VideoShapeConfigWidget.h"

#include <KOdfXmlNS.h>
#include "KShapeControllerBase.h"
#include <KShapeLoadingContext.h>
#include "VideoCollection.h"

#include <klocale.h>
#include <kdebug.h>

VideoShapeFactory::VideoShapeFactory(QObject *parent)
    : KShapeFactoryBase(parent, VIDEOSHAPEID, i18n("Video"))
{
    setToolTip(i18n("Video, embedded or fullscreen"));
    setIcon("video-x-generic");
    setOdfElementNames(KOdfXmlNS::draw, QStringList("plugin"));
    setLoadingPriority(1);
}

KShape *VideoShapeFactory::createDefaultShape(KResourceManager *documentResources) const
{
    VideoShape * defaultShape = new VideoShape();
    defaultShape->setShapeId(VIDEOSHAPEID);
    if (documentResources) {
          Q_ASSERT(documentResources->hasResource(VideoCollection::ResourceId));
          QVariant vc = documentResources->resource(VideoCollection::ResourceId);
          defaultShape->setVideoCollection(static_cast<VideoCollection*>(vc.value<void*>()));
    }
    return defaultShape;
}

bool VideoShapeFactory::supports(const KXmlElement &e, KShapeLoadingContext &context) const
{
    Q_UNUSED(context);
    return e.localName() == "plugin" && e.namespaceURI() == KOdfXmlNS::draw;
}

void VideoShapeFactory::newDocumentResourceManager(KResourceManager *manager)
{
    QVariant variant;
    variant.setValue<void*>(new VideoCollection(manager));
    manager->setResource(VideoCollection::ResourceId, variant);
}

QList<KShapeConfigWidgetBase*> VideoShapeFactory::createShapeOptionPanels()
{
    QList<KShapeConfigWidgetBase*> panels;
    panels.append(new VideoShapeConfigWidget());
    return panels;
}
