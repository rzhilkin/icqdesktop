#include "stdafx.h"

#include "../../../utils/utils.h"

#include "MessageContentWidget.h"

namespace HistoryControl
{

	MessageContentWidget::MessageContentWidget(QWidget *parent, const bool isOutgoing, QString _aimId)
		: QWidget(parent)
        , Initialized_(false)
		, IsOutgoing_(isOutgoing)
        , CurrentProcessId_(0)
        , Selected_(false)
        , aimId_(_aimId)
	{
	}

	MessageContentWidget::~MessageContentWidget()
	{

	}


    QPoint MessageContentWidget::deliveryStatusOffsetHint(const int32_t statusLineWidth) const
    {
        (void)statusLineWidth;

        return QPoint();
    }

    bool MessageContentWidget::canReplace() const
    {
        return true;
    }

    bool MessageContentWidget::hasTextBubble() const
    {
        return false;
    }

    bool MessageContentWidget::isSelected() const
    {
        return Selected_;
    }

    void MessageContentWidget::select(const bool value)
    {
        Selected_ = value;
        update();
    }

    bool MessageContentWidget::selectByPos(const QPoint &pos)
    {
        assert(hasTextBubble());

        (void)pos;

        return false;
    }

    void MessageContentWidget::clearSelection()
    {
        assert(hasTextBubble());
    }

    void MessageContentWidget::onVisibilityChanged(const bool isVisible)
    {
        if (isVisible && !Initialized_)
        {
            Initialized_ = true;
            initialize();
        }
    }

    QString MessageContentWidget::selectedText() const
    {
        return QString();
    }

    QString MessageContentWidget::toRecentsString() const
    {
        return toString();
    }

    int MessageContentWidget::maxWidgetWidth() const
    {
        return -1;
    }

	bool MessageContentWidget::isOutgoing() const
	{
		return IsOutgoing_;
	}

    int64_t MessageContentWidget::getCurrentProcessId() const
    {
        assert(CurrentProcessId_ >= 0);

        return CurrentProcessId_;
    }

    bool MessageContentWidget::isCurrentProcessId(const int64_t id) const
    {
        assert(id > 0);
        assert(CurrentProcessId_ >= 0);

        return (CurrentProcessId_ == id);
    }

    void MessageContentWidget::resetCurrentProcessId()
    {
        CurrentProcessId_ = 0;
    }

    void MessageContentWidget::setCurrentProcessId(const int64_t id)
    {
        assert(CurrentProcessId_ == 0);
        assert(id > 0);

        CurrentProcessId_ = id;
    }

	void MessageContentWidget::setFixedSize(const QSize &size)
	{
		setFixedSize(size.width(), size.height());
	}

	void MessageContentWidget::setFixedSize(const int32_t w, const int32_t h)
	{
		assert(w >= 0);
		assert(h >= 0);

		const auto isSizeChanged = ((width() != w) || (height() != h));
		if (!isSizeChanged)
		{
			return;
		}

		QWidget::setFixedSize(w, h);
	}

    void MessageContentWidget::initialize()
    {
    }

	void MessageContentWidget::paintEvent(QPaintEvent*)
	{
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);
		p.setRenderHint(QPainter::SmoothPixmapTransform);
		p.setRenderHint(QPainter::TextAntialiasing);

		const auto margins = contentsMargins();
		p.translate(margins.left(), margins.top());

		render(p);
	}


    void MessageContentWidget::mouseMoveEvent(QMouseEvent *e)
    {
        const auto isLeftButtonPressed = ((e->buttons() & Qt::LeftButton) != 0);
        if (isLeftButtonPressed)
        {
            auto pos = e->pos();
            if (mousePos_.isNull())
            {
                mousePos_ = pos;
            }
            else if (!mousePos_.isNull() && (abs(mousePos_.x() - pos.x()) > Utils::GetDragDistance() || abs(mousePos_.y() - pos.y()) > Utils::GetDragDistance()))
            {
                mousePos_ = QPoint();
                drag();
                return;
            }
        }
        else
        {
            mousePos_ = QPoint();
        }

        return QWidget::mouseMoveEvent(e);
    }
}