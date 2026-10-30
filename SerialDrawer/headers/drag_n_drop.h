#ifndef DRAG_N_DROP
#define DRAG_N_DROP

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QUrl>

class Drag_n_Drop : public QLabel
{
    Q_OBJECT
public:
    explicit Drag_n_Drop(QWidget *parent = nullptr) : QLabel(parent) {
        // 1. Вмикаємо прийом подій Drag & Drop
        setAcceptDrops(true); 
        setAlignment(Qt::AlignCenter);
        setText("Перетягніть зображення сюди");
        setStyleSheet("QLabel { border: 2px dashed #999; background-color: #f0f0f0; }");
        setFixedSize(200,120);
    }

protected:
    // 2. Обробка моменту, коли об'єкт потрапляє на віджет
    void dragEnterEvent(QDragEnterEvent *event) override {
        // Перевіряємо, чи містить об'єкт файли (URLs) або графічні дані
        if (event->mimeData()->hasUrls() || event->mimeData()->hasImage()) {
            event->acceptProposedAction(); // Дозволяємо скидання
        } else {
            event->ignore();
        }
    }

    // 3. Обробка моменту відпускання кнопки миші (саме "скидання")
    void dropEvent(QDropEvent *event) override {
        const QMimeData *mimeData = event->mimeData();
        QPixmap pixmap;

        if (mimeData->hasUrls()) {
            // Якщо перетягнули файл (наприклад, з робочого столу)
            QString localFile = mimeData->urls().first().toLocalFile();
            pixmap.load(localFile);
        } else if (mimeData->hasImage()) {
            // Якщо перетягнули саму картинку (наприклад, з веб-сторінки)
            pixmap = qvariant_cast<QPixmap>(mimeData->imageData());
        }

        if (!pixmap.isNull()) {
            // Масштабуємо картинку під розмір віджета зі збереженням пропорцій
            setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            event->acceptProposedAction();
        }
    }
};
#endif