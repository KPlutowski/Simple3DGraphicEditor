#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius, int meridians, int parallels, wxColour color) : Sphere(Position(x, y, z), radius, meridians, parallels, color) {}
Sphere::Sphere(Position center, double radius, int meridians, int parallels, wxColour color) :Drawable(color), _center(center), _radius(radius), _meridians(meridians), _parallels(parallels) {}

void Sphere::move(double x_shift, double y_shift, double z_shift) {
    _center.x += x_shift;
    _center.y += y_shift;
    _center.z += z_shift;
}

void Sphere::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
    // Move center to origin
    move(-x_cord, -y_cord, -z_cord);

    std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha, beta, gamma);

    double x = _center.x * rotationMatrix[0][0] + _center.y * rotationMatrix[0][1] + _center.z * rotationMatrix[0][2];
    double y = _center.x * rotationMatrix[1][0] + _center.y * rotationMatrix[1][1] + _center.z * rotationMatrix[1][2];
    double z = _center.x * rotationMatrix[2][0] + _center.y * rotationMatrix[2][1] + _center.z * rotationMatrix[2][2];

    _center.x = x;
    _center.y = y;
    _center.z = z;

    // Move center back to original position
    move(x_cord, y_cord, z_cord);
}

void Sphere::draw_front(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            Position v1(
                _center.x + _radius * sin(phi) * cos(lambda),
                _center.y + _radius * sin(phi) * sin(lambda),
                _center.z + _radius * cos(phi)
            );
            Position v2(
                _center.x + _radius * sin(phi) * cos(next_lambda),
                _center.y + _radius * sin(phi) * sin(next_lambda),
                _center.z + _radius * cos(phi)
            );
            Position v3(
                _center.x + _radius * sin(next_phi) * cos(next_lambda),
                _center.y + _radius * sin(next_phi) * sin(next_lambda),
                _center.z + _radius * cos(next_phi)
            );
            Position v4(
                _center.x + _radius * sin(next_phi) * cos(lambda),
                _center.y + _radius * sin(next_phi) * sin(lambda),
                _center.z + _radius * cos(next_phi)
            );

            // Project vertices to 2D screen coordinates
            wxPoint p1 = Camera::projectFront(v1);
            wxPoint p2 = Camera::projectFront(v2);
            wxPoint p3 = Camera::projectFront(v3);
            wxPoint p4 = Camera::projectFront(v4);

            // Draw quad
            dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
            dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
            dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
            dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
        }
    }
}

void Sphere::draw_top(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            Position v1(
                _center.x + _radius * sin(phi) * cos(lambda),
                _center.y + _radius * sin(phi) * sin(lambda),
                _center.z + _radius * cos(phi)
            );
            Position v2(
                _center.x + _radius * sin(phi) * cos(next_lambda),
                _center.y + _radius * sin(phi) * sin(next_lambda),
                _center.z + _radius * cos(phi)
            );
            Position v3(
                _center.x + _radius * sin(next_phi) * cos(next_lambda),
                _center.y + _radius * sin(next_phi) * sin(next_lambda),
                _center.z + _radius * cos(next_phi)
            );
            Position v4(
                _center.x + _radius * sin(next_phi) * cos(lambda),
                _center.y + _radius * sin(next_phi) * sin(lambda),
                _center.z + _radius * cos(next_phi)
            );

            // Project vertices to 2D screen coordinates
            wxPoint p1 = Camera::projectTop(v1);
            wxPoint p2 = Camera::projectTop(v2);
            wxPoint p3 = Camera::projectTop(v3);
            wxPoint p4 = Camera::projectTop(v4);

            // Draw quad
            dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
            dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
            dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
            dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
        }
    }
}

void Sphere::draw_side(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            Position v1(
                _center.x + _radius * sin(phi) * cos(lambda),
                _center.y + _radius * sin(phi) * sin(lambda),
                _center.z + _radius * cos(phi)
            );
            Position v2(
                _center.x + _radius * sin(phi) * cos(next_lambda),
                _center.y + _radius * sin(phi) * sin(next_lambda),
                _center.z + _radius * cos(phi)
            );
            Position v3(
                _center.x + _radius * sin(next_phi) * cos(next_lambda),
                _center.y + _radius * sin(next_phi) * sin(next_lambda),
                _center.z + _radius * cos(next_phi)
            );
            Position v4(
                _center.x + _radius * sin(next_phi) * cos(lambda),
                _center.y + _radius * sin(next_phi) * sin(lambda),
                _center.z + _radius * cos(next_phi)
            );

            // Project vertices to 2D screen coordinates
            wxPoint p1 = Camera::projectSide(v1);
            wxPoint p2 = Camera::projectSide(v2);
            wxPoint p3 = Camera::projectSide(v3);
            wxPoint p4 = Camera::projectSide(v4);

            // Draw quad
            dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
            dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
            dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
            dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
        }
    }
}

void Sphere::draw_perspective(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    // Iterate over parallels
    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            wxPoint p1_2d = Camera::projectPerspective(Position(_center.x + _radius * sin(phi) * cos(lambda), _center.y + _radius * sin(phi) * sin(lambda), _center.z + _radius * cos(phi)));
            wxPoint p2_2d = Camera::projectPerspective(Position(_center.x + _radius * sin(phi) * cos(next_lambda), _center.y + _radius * sin(phi) * sin(next_lambda), _center.z + _radius * cos(phi)));
            wxPoint p3_2d = Camera::projectPerspective(Position(_center.x + _radius * sin(next_phi) * cos(next_lambda), _center.y + _radius * sin(next_phi) * sin(next_lambda), _center.z + _radius * cos(next_phi)));
            wxPoint p4_2d = Camera::projectPerspective(Position(_center.x + _radius * sin(next_phi) * cos(lambda), _center.y + _radius * sin(next_phi) * sin(lambda), _center.z + _radius * cos(next_phi)));

            // Draw quad
            dc.DrawLine(p1_2d.x, p1_2d.y, p2_2d.x, p2_2d.y);
            dc.DrawLine(p2_2d.x, p2_2d.y, p3_2d.x, p3_2d.y);
            dc.DrawLine(p3_2d.x, p3_2d.y, p4_2d.x, p4_2d.y);
            dc.DrawLine(p4_2d.x, p4_2d.y, p1_2d.x, p1_2d.y);
        }
    }
}

void Sphere::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) {
    draw_front(dc1);
    draw_top(dc2);
    draw_side(dc3);
    draw_perspective(dc4);
}

std::string Sphere::save() const
{
    std::string result = "Sphere "
        + std::to_string(_center.x) + " " + std::to_string(_center.y) + " " + std::to_string(_center.z) + " "
        + std::to_string(_radius) + " " + std::to_string(_meridians) + " " + std::to_string(_parallels) + " "
        + std::to_string(_color.GetRGB()) + "\n";
    return result;
}
