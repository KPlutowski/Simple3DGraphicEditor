#pragma once
#include "Drawable.h"

/**
 * @brief A class representing a box object that can be drawn on a 2D canvas from different perspectives.
 */
class Box : public Drawable {
public:
    /**
     * @brief Constructs a box object with specified coordinates for two opposite corners.
     * @param x1 - The X-coordinate of the first corner.
     * @param y1 - The Y-coordinate of the first corner.
     * @param z1 - The Z-coordinate of the first corner.
     * @param x2 - The X-coordinate of the second corner.
     * @param y2 - The Y-coordinate of the second corner.
     * @param z2 - The Z-coordinate of the second corner.
     * @param color - The color of the box.
     */
    Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color = Drawable::line_color);

    /**
     * @brief Constructs a box object with specified coordinates for two opposite corners.
     * @param start - The position of the first corner.
     * @param end - The position of the second corner.
     * @param color - The color of the box.
     */
    Box(const Position& start, const Position& end, const wxColour& color = Drawable::line_color);

    /**
     * @brief Draws the box on four different 2D canvases representing different perspectives.
     * @param dc1 - The device context for the front view.
     * @param dc2 - The device context for the top view.
     * @param dc3 - The device context for the side view.
     * @param dc4 - The device context for the perspective view.
     */
    virtual void draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) override;

protected:
    void move(double x_shift, double y_shift, double z_shift) override;
    void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) override;
    void draw_front(wxDC& dc) override;
    void draw_top(wxDC& dc) override;
    void draw_side(wxDC& dc) override;
    void draw_perspective(wxDC& dc) override;
    std::string save() const override;

private:
    std::vector<Position> _corners; ///< The positions of all eight corners of the box.
};