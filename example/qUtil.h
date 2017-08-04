#ifndef __QT_UTIL_H__
#define __QT_UTIL_H__

#include <QPoint>

static inline qreal getX(qreal y, const QPointF& p1, const QPointF& p2)
{
	return (p1.x() - p2.x()) / (p1.y() - p2.y()) * (y - p2.y()) + p2.x();
}

static inline qreal getY(qreal x, const QPointF& p1, const QPointF& p2)
{
	return (p1.y() - p2.y()) / (p1.x() - p2.x()) * (x - p2.x()) + p2.y();
}

#endif // __QT_UTIL_H__
