/**
 * Copyright 2017 ghabxph(c)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "cartesian.h"
#define CONSOLE_WIDTH  959
#define CONSOLE_HEIGHT 418

/// Renders the Cartesian plane
void Cartesian::renderFunction(CartesianFunction *cartesianFunction, double minValue, double maxValue, double iterations, double zoomX, double zoomY)
{
    /// Get console handle
    HWND hConsole = GetConsoleWindow();
    /// Get a handle to device context
    HDC hDeviceContext = GetDC(hConsole);

    double step = abs(maxValue - minValue) / iterations;

    /// Color palette
    COLORREF XEE = RGB(0xEE, 0xEE, 0xEE);
    COLORREF X33 = RGB(0x33, 0x33, 0x33);

    while (true) {
        for (int i = 0; i < CONSOLE_WIDTH; i++) {
            SetPixel(hDeviceContext, i, CONSOLE_HEIGHT / 2, X33);
        }
        for (int i = 0; i < CONSOLE_HEIGHT; i++) {
            SetPixel(hDeviceContext, CONSOLE_WIDTH / 2, i, X33);
        }
        double x = minValue;
        for (int i = 0; i < iterations; i++) {
            x += step;
            plot(hDeviceContext, x, cartesianFunction->f(x), XEE, CONSOLE_WIDTH / zoomX, CONSOLE_HEIGHT / zoomY);
        }
    }

    ReleaseDC(hConsole, hDeviceContext);
    delete cartesianFunction;
}

#define CARTESIAN_PLOT(x,y) SetPixel(hDeviceContext, (CONSOLE_WIDTH / 2) + x, (CONSOLE_HEIGHT / 2) - y, color)
/// Plots a specific point in the Cartesian plane
void Cartesian::plot (HDC hDeviceContext, double x, double y, COLORREF color, double xUnitPerDot, double yUnitPerDot)
{
    int xUnit = (int)(x * 4 * xUnitPerDot);
    int yUnit = (int)(y * 4 * yUnitPerDot);
    CARTESIAN_PLOT(xUnit - 1, yUnit + 1);
    CARTESIAN_PLOT(xUnit + 0, yUnit + 1);
    CARTESIAN_PLOT(xUnit + 1, yUnit + 1);

    CARTESIAN_PLOT(xUnit - 1, yUnit + 0);
    CARTESIAN_PLOT(xUnit + 0, yUnit + 0);
    CARTESIAN_PLOT(xUnit + 1, yUnit + 0);

    CARTESIAN_PLOT(xUnit - 1, yUnit - 1);
    CARTESIAN_PLOT(xUnit + 0, yUnit - 1);
    CARTESIAN_PLOT(xUnit + 1, yUnit - 1);
}
