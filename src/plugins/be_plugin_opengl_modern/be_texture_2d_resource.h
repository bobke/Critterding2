#ifndef BE_TEXTURE_2D_RESOURCE_H_INCLUDED
#define BE_TEXTURE_2D_RESOURCE_H_INCLUDED

#include "graphics/be_texture.h"
#include "be_worker_pool.h"
// #include "utils/settings.h"
#include <boost/thread/future.hpp>
#include <QImage>
// #include <QOpenGLWidget>

class BeTexture2DResource
{
public:
	
	enum Status
	{
		eStatusLoading,
		eStatusError,
		eStatusReady
	};

	BeTexture2DResource(boost::shared_ptr<BeWorkerPool> threadPool, const std::string& path) : m_status(eStatusLoading)
	{
		m_futureImage=threadPool->schedule< boost::shared_ptr<QImage> >(boost::bind(&BeTexture2DResource::loadImage, this, path));
		m_texture=boost::shared_ptr<BeTexture2D>(new BeTexture2D);
	}

	boost::shared_ptr<BeTexture2D> get()
	{
		return isReady() ? m_texture : boost::shared_ptr<BeTexture2D>();
	}

	void update()
	{
		if(m_status==eStatusLoading)
		{
			if(m_futureImage.is_ready())
			{
				boost::shared_ptr<QImage> image=m_futureImage.get();
				if(image->bits())
				{
					// FIXME get the format from the image
//                     m_texture->data(0, 4, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->bits());
// 	                    m_texture->data(0, 4, image->width(), image->height(), 0, image->format(), GL_UNSIGNED_BYTE, image->bits());
	                    m_texture->data(0, GL_RGB, image->width(), image->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image->bits());

					m_texture->parameter(GL_TEXTURE_MAX_LEVEL,4);
					m_texture->parameter(GL_TEXTURE_MAX_LOD,4);

                    m_texture->parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    m_texture->parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    m_texture->parameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
//                     m_texture->parameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, Settings::Instance()->getCVar("texture_anisotropy"));
					
                    m_texture->generateMipmap();
					m_status=eStatusReady;
				}
				else
				{
					m_status=eStatusError;
				}
			}
		}
	}

	bool isReady()
	{
		update();
		return m_status==eStatusReady;
	}

private:

	boost::shared_ptr<QImage> loadImage(const std::string& path)
	{
		QImage* imageBP = new QImage(path.c_str());
		
		// copy over a converted format
		*imageBP = imageBP->convertToFormat(QImage::Format_ARGB32_Premultiplied, Qt::AutoColor);
// 		*imageBP = imageBP->convertToFormat(QImage::Format_RGBA64_Premultiplied);
		
// 		imageBP->convertToFormat(QImage::Format_Grayscale8);
// 		imageBP->convertToFormat(QImage::Format_RGBA64_Premultiplied);
		
//          = new QImage(QImage::); //   // flipped 32bit RGBA
//         QImage* imageBP = new QImage(QOpenGLWidget::convertToGLFormat(QImage(path.c_str()))); //   // flipped 32bit RGBA
        return boost::shared_ptr<QImage>(imageBP);
	}

	Status m_status;
	boost::shared_ptr<BeTexture2D> m_texture;
	boost::shared_future< boost::shared_ptr<QImage> > m_futureImage;

};

#endif
 
