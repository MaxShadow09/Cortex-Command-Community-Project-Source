#ifndef _ALLEGROBITMAP_
#define _ALLEGROBITMAP_

//////////////////////////////////////////////////////////////////////////////////////////
// File:            AllegroBitmap.h
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     AllegroBitmap class
// Project:         GUI Library
// Author(s):       Jason Boettcher
//                  jackal@shplorb.com
//                  www.shplorb.com/~jackal

#include "GUI/Interface.h"
#include "ContentFile.h"
#include "allegro.h"

namespace RTE
{

class ContentFile;


//////////////////////////////////////////////////////////////////////////////////////////
// Class:           AllegroBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     A bitmap interface using the CDX Library bitmap
// Parent(s):       GUIBitmap
// Class history:   12/30/2003 CDXSurfaceInterface Created.
//                  11/09/2005 Renamed to AllegroBitmap and ported to use Allegro instead of CDX.

class AllegroBitmap :
    public GUIBitmap
{

//////////////////////////////////////////////////////////////////////////////////////////
// Public member variable, method and friend function declarations

public:

//////////////////////////////////////////////////////////////////////////////////////////
// Constructor:     AllegroBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Constructor method used to instantiate a AllegroBitmap object in 
//                  system memory.

    AllegroBitmap();


//////////////////////////////////////////////////////////////////////////////////////////
// Constructor:     AllegroBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Constructor method used to instantiate a AllegroBitmap object in 
//                  system memory.
// Arguments:       BITMAP, ownership is NOT transferred!

    AllegroBitmap(BITMAP *pBitmap);


//////////////////////////////////////////////////////////////////////////////////////////
// Destructor:      ~AllegroBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Destructor method used to clean up a AllegroBitmap object before deletion
//                  from system memory.
// Arguments:       None.

	~AllegroBitmap() override { Destroy(); }


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          Create
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Creates a blank bitmap
// Arguments:       Width & Height and color depth (8 or 32)

    bool Create(int Width, int Height, int Depth = 8);


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          Create
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Creates the bitmap from a filename
// Arguments:       CDXScreen, Filename

    bool Create(const std::string Filename);


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual method:  Destroy
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Destroys and frees the bitmap
// Arguments:       None.

	void Destroy() override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          Draw
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Draw a section of this bitmap onto another bitmap
// Arguments:       Destination Bitmap, Position, Size

    void Draw(GUIBitmap *pDestBitmap, int X, int Y, GUIRect *pRect);


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          DrawTrans
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Draw a section of this bitmap onto another bitmap ignoring 
//                  color-keyed pixels
// Arguments:       Destination Bitmap, Position, Size

    void DrawTrans(GUIBitmap *pDestBitmap, int X, int Y, GUIRect *pRect);


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  DrawTransScaled
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Draw this bitmap scaled onto another bitmap ignoring color-keyed pixels.
// Arguments:       Destination Bitmap, Position, Size

	void DrawTransScaled(GUIBitmap *pDestBitmap, int X, int Y, int width, int height) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  DrawLine
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Draws a line.
// Arguments:       Start Position, End Position, Color.

	void DrawLine(int x1, int y1, int x2, int y2, unsigned long Color) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          DrawRectangle
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Draws a rectangle.
// Arguments:       Position, Size, Color, Filled.

    void DrawRectangle(int X, int Y, int Width, int Height, unsigned long Color, bool Filled) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          GetPixel
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the colour of a pixel at a specific point.
// Arguments:       Point.

    unsigned long GetPixel(int X, int Y) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          SetPixel
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Sets the color of a pixel at a specific point.
// Arguments:       Point, Color.

    void SetPixel(int X, int Y, unsigned long Color) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          GetWidth
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the Width of the bitmap.
// Arguments:       None.

    int GetWidth() const override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          GetHeight
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the Height of the bitmap.
// Arguments:       None.

    int GetHeight() const override;

/* NA, color key is always 0 with allegro
//////////////////////////////////////////////////////////////////////////////////////////
// Method:          SetColorKey
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Sets the color key of the bitmap.
// Arguments:       ColorKey.

    void SetColorKey(unsigned long Key);


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  GetColorKey
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Sets the color key of the bitmap to teh color of the pixel in teh
//                  upper right corner of the bitmap.
// Arguments:       ColorKey.

    void GetColorKey();
*/

//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  GetColorDepth
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the number of bits per pixel color depth of this bitmap.
// Returns:         8, 16, 32 etc

	int GetColorDepth() override;


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  GetClipRect
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the clipping rectangle of the bitmap.
// Arguments:       Pointer to GUIRect struct to fill out.

	void GetClipRect(GUIRect *Rect) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          SetClipRect
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Sets the clipping rectangle of the bitmap.
// Arguments:       Rectangle pointer. 0 for no clipping.

	void SetClipRect(GUIRect *pRect) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual Method:  AddClipRect
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Sets the clipping rectangle of the specified bitmap as the
//                  intersection of its current clipping rectangle and the rectangle
//                  described by the passed-in rect. 
// Arguments:       Rectangle pointer.

	void AddClipRect(GUIRect *Rect) override;


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual method:  GetDataPath
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Returns the path to the datafile object this GUIBitmap uses.
// Arguments:       None.

	std::string GetDataPath() override;


//////////////////////////////////////////////////////////////////////////////////////////
// Method:          GetBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Gets the BITMAP.
// Arguments:       None.

    BITMAP * GetBitmap();

	/// <summary>
	/// Gets a pointer to the const BITMAP.
	/// </summary>
	/// <returns></returns>
	const BITMAP * GetConstBitmap() const;


//////////////////////////////////////////////////////////////////////////////////////////
// Virtual method:  HasBitmap
//////////////////////////////////////////////////////////////////////////////////////////
// Description:     Indicates whether this GUI bitmap even contains loaded bitmap data.
// Arguments:       None.
// Returns:         Whether this contains bitmap data or not.

	bool HasBitmap() override { return m_pBitmap != 0; }


//////////////////////////////////////////////////////////////////////////////////////////
// Private member variable and method declarations

private:

    ContentFile     m_BitmapFile;
    // This is not owned, unless m_SelfCreated is true
    BITMAP          *m_pBitmap;
    bool            m_SelfCreated;

};


}; // namespace RTE


#endif  // File