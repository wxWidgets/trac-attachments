import wx

def copyImageToClipboard(image):
    if not wx.TheClipboard.IsOpened():
        wx.TheClipboard.Open()
        bitmap = wx.Bitmap(image)
        data_object = wx.BitmapDataObject()
        data_object.SetBitmap(bitmap)
        success = wx.TheClipboard.SetData(data_object)
        wx.TheClipboard.Close()
    else:
        success = False
    return success


def getBlankImage(width, height, colour):
    r, g, b, a = colour.Get(includeAlpha=True)
    data = bytearray((r, g, b) * width * height)
    alpha = bytearray((a,) * height * width)
    image = wx.Image(width, height, data, alpha)
    return image


def getClipboardImage():
    bitmap = None
    if not wx.TheClipboard.IsOpened():
        data_obj = wx.BitmapDataObject()
        wx.TheClipboard.Open()
        success = wx.TheClipboard.GetData(data_obj)
        wx.TheClipboard.Close()
        if success:
            bitmap = data_obj.GetBitmap()
    if bitmap is not None:
        return bitmap.ConvertToImage()
    return None


def runTest(extra_colour=None):
    print("extra_colour =", extra_colour)
    bg_colour = wx.Colour(255, 255, 255, 0)
    start_image = getBlankImage(16, 16, bg_colour)
    if extra_colour is not None:
        # Set one pixel to the extra colour
        x, y = 0, 0
        r, g, b, a = extra_colour.Get(includeAlpha=True)
        start_image.SetRGB(x, y, r, g, b)
        start_image.SetAlpha(x, y, a)
    print("start_image.HasAlpha() =", start_image.HasAlpha())
    success = copyImageToClipboard(start_image)
    assert success
    clipboard_image = getClipboardImage()
    assert clipboard_image.IsOk()
    print("clipboard_image.HasAlpha() =", clipboard_image.HasAlpha())


def main():
    _app = wx.App()
    print("All fully transparent pixels:")
    runTest(None)
    print("\nOne fully opaque pixel:")
    runTest(wx.Colour(255, 0, 0, 255))
    print("\nOne partially transparent pixel:")
    runTest(wx.Colour(255, 0, 0, 1))
    print("\nOne partially transparent pixel:")
    runTest(wx.Colour(255, 0, 0, 254))


if __name__ == '__main__':
    main()

