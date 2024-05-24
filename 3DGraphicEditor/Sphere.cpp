#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius, int meridians, int parallels) : _center(x, y, z), _radius(radius), _meridians(meridians), _parallels(parallels), _color(line_color) {}
Sphere::Sphere(Position center, double radius, int meridians, int parallels) :Sphere(center.x,center.y,center.z,radius,meridians,parallels){}

void Sphere::move(double x_shift, double y_shift, double z_shift) {
    _center.x += x_shift;
    _center.y += y_shift;
    _center.z += z_shift;
}

void Sphere::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
    // Move center to origin
    move(-x_cord, -y_cord, -z_cord);

    std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha, beta, gamma);

    double sx = _center.x * rotationMatrix[0][0] + _center.y * rotationMatrix[0][1] + _center.z * rotationMatrix[0][2];
    double sy = _center.x * rotationMatrix[1][0] + _center.y * rotationMatrix[1][1] + _center.z * rotationMatrix[1][2];
    double sz = _center.x * rotationMatrix[2][0] + _center.y * rotationMatrix[2][1] + _center.z * rotationMatrix[2][2];

    _center.x = sx;
    _center.y = sy;
    _center.z = sz;

    // Move center back to original position
    move(x_cord, y_cord, z_cord);
}

void Sphere::draw_front(wxDC& dc) {
    dc.SetPen(wxPen(_color));

    double phi_step = M_PI / _parallels;
    double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            double x1 = _center.x + _radius * sin(phi) * cos(lambda);
            double y1 = _center.y + _radius * sin(phi) * sin(lambda);
            double x2 = _center.x + _radius * sin(phi) * cos(next_lambda);
            double y2 = _center.y + _radius * sin(phi) * sin(next_lambda);
            double x3 = _center.x + _radius * sin(next_phi) * cos(next_lambda);
            double y3 = _center.y + _radius * sin(next_phi) * sin(next_lambda);
            double x4 = _center.x + _radius * sin(next_phi) * cos(lambda);
            double y4 = _center.y + _radius * sin(next_phi) * sin(lambda);

            // Draw quad
            dc.DrawLine(x1, y1, x2, y2);
            dc.DrawLine(x2, y2, x3, y3);
            dc.DrawLine(x3, y3, x4, y4);
            dc.DrawLine(x4, y4, x1, y1);
        }
    }
}

void Sphere::draw_top(wxDC& dc) {
    dc.SetPen(wxPen(_color));

    double phi_step = M_PI / _parallels;
    double lambda_step = 2 * M_PI / _meridians;

    // Iterate over meridians
    for (int j = 0; j < _meridians; ++j) {
        double lambda = j * lambda_step;
        double next_lambda = (j + 1) * lambda_step;

        // Iterate over parallels
        for (int i = 0; i < _parallels; ++i) {
            double phi = i * phi_step;
            double next_phi = (i + 1) * phi_step;

            // Compute vertices
            double x1 = _center.x + _radius * sin(phi) * cos(lambda);
            double z1 = _center.z + _radius * cos(phi);
            double x2 = _center.x + _radius * sin(phi) * cos(next_lambda);
            double z2 = _center.z + _radius * cos(phi);
            double x3 = _center.x + _radius * sin(next_phi) * cos(next_lambda);
            double z3 = _center.z + _radius * cos(next_phi);
            double x4 = _center.x + _radius * sin(next_phi) * cos(lambda);
            double z4 = _center.z + _radius * cos(next_phi);

            // Draw quad
            dc.DrawLine(x1, z1, x2, z2);
            dc.DrawLine(x2, z2, x3, z3);
            dc.DrawLine(x3, z3, x4, z4);
            dc.DrawLine(x4, z4, x1, z1);
        }
    }
}

void Sphere::draw_side(wxDC& dc) {
    dc.SetPen(wxPen(_color));

    double phi_step = M_PI / _parallels;
    double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            double y1 = _center.y + _radius * sin(phi) * sin(lambda);
            double z1 = _center.z + _radius * cos(phi);
            double y2 = _center.y + _radius * sin(phi) * sin(next_lambda);
            double z2 = _center.z + _radius * cos(phi);
            double y3 = _center.y + _radius * sin(next_phi) * sin(next_lambda);
            double z3 = _center.z + _radius * cos(next_phi);
            double y4 = _center.y + _radius * sin(next_phi) * sin(lambda);
            double z4 = _center.z + _radius * cos(next_phi);

            // Draw quad
            dc.DrawLine(y1, z1, y2, z2);
            dc.DrawLine(y2, z2, y3, z3);
            dc.DrawLine(y3, z3, y4, z4);
            dc.DrawLine(y4, z4, y1, z1);
        }
    }
}

void Sphere::draw_perspective(wxDC& dc) {
    dc.SetPen(wxPen(_color));

    // Compute camera direction
    Position camera_dir = {
        camera_look.x - camera_pos.x,
        camera_look.y - camera_pos.y,
        camera_look.z - camera_pos.z
    };

    // Normalize camera direction
    double length = sqrt(camera_dir.x * camera_dir.x + camera_dir.y * camera_dir.y + camera_dir.z * camera_dir.z);
    camera_dir.x /= length;
    camera_dir.y /= length;
    camera_dir.z /= length;

    // Convert field of view to radians
    double fov_rad = camera_fov * M_PI / 180.0;

    // Compute screen dimensions
    int screen_width = dc.GetSize().GetWidth();
    int screen_height = dc.GetSize().GetHeight();

    // Iterate over all vertices of the sphere
    for (int i = 0; i < _parallels; ++i) {
        double phi1 = i * M_PI / _parallels;
        double phi2 = (i + 1) * M_PI / _parallels;
        for (int j = 0; j < _meridians; ++j) {
            double lambda1 = j * 2 * M_PI / _meridians;
            double lambda2 = (j + 1) * 2 * M_PI / _meridians;

            // Compute vertices positions in 3D
            double x1 = _center.x + _radius * sin(phi1) * cos(lambda1);
            double y1 = _center.y + _radius * sin(phi1) * sin(lambda1);
            double z1 = _center.z + _radius * cos(phi1);

            double x2 = _center.x + _radius * sin(phi1) * cos(lambda2);
            double y2 = _center.y + _radius * sin(phi1) * sin(lambda2);
            double z2 = _center.z + _radius * cos(phi1);

            double x3 = _center.x + _radius * sin(phi2) * cos(lambda2);
            double y3 = _center.y + _radius * sin(phi2) * sin(lambda2);
            double z3 = _center.z + _radius * cos(phi2);

            double x4 = _center.x + _radius * sin(phi2) * cos(lambda1);
            double y4 = _center.y + _radius * sin(phi2) * sin(lambda1);
            double z4 = _center.z + _radius * cos(phi2);

            // Compute vectors from camera to vertices
            double vec1_x = x1 - camera_pos.x;
            double vec1_y = y1 - camera_pos.y;
            double vec1_z = z1 - camera_pos.z;

            double vec2_x = x2 - camera_pos.x;
            double vec2_y = y2 - camera_pos.y;
            double vec2_z = z2 - camera_pos.z;

            double vec3_x = x3 - camera_pos.x;
            double vec3_y = y3 - camera_pos.y;
            double vec3_z = z3 - camera_pos.z;

            double vec4_x = x4 - camera_pos.x;
            double vec4_y = y4 - camera_pos.y;
            double vec4_z = z4 - camera_pos.z;

            // Compute dot products of camera direction and vectors to vertices
            double dot_product1 = vec1_x * camera_dir.x + vec1_y * camera_dir.y + vec1_z * camera_dir.z;
            double dot_product2 = vec2_x * camera_dir.x + vec2_y * camera_dir.y + vec2_z * camera_dir.z;
            double dot_product3 = vec3_x * camera_dir.x + vec3_y * camera_dir.y + vec3_z * camera_dir.z;
            double dot_product4 = vec4_x * camera_dir.x + vec4_y * camera_dir.y + vec4_z * camera_dir.z;

            // Apply perspective projection
            double projected_x1 = (screen_width / 2.0) + (vec1_x / (tan(fov_rad / 2.0) * dot_product1)) * (screen_width / 2.0);
            double projected_y1 = (screen_height / 2.0) - (vec1_y / (tan(fov_rad / 2.0) * dot_product1)) * (screen_height / 2.0);

            double projected_x2 = (screen_width / 2.0) + (vec2_x / (tan(fov_rad / 2.0) * dot_product2)) * (screen_width / 2.0);
            double projected_y2 = (screen_height / 2.0) - (vec2_y / (tan(fov_rad / 2.0) * dot_product2)) * (screen_height / 2.0);

            double projected_x3 = (screen_width / 2.0) + (vec3_x / (tan(fov_rad / 2.0) * dot_product3)) * (screen_width / 2.0);
            double projected_y3 = (screen_height / 2.0) - (vec3_y / (tan(fov_rad / 2.0) * dot_product3)) * (screen_height / 2.0);

            double projected_x4 = (screen_width / 2.0) + (vec4_x / (tan(fov_rad / 2.0) * dot_product4)) * (screen_width / 2.0);
            double projected_y4 = (screen_height / 2.0) - (vec4_y / (tan(fov_rad / 2.0) * dot_product4)) * (screen_height / 2.0);

            // Draw lines
            dc.DrawLine(projected_x1, projected_y1, projected_x2, projected_y2);
            dc.DrawLine(projected_x2, projected_y2, projected_x3, projected_y3);
            dc.DrawLine(projected_x3, projected_y3, projected_x4, projected_y4);
            dc.DrawLine(projected_x4, projected_y4, projected_x1, projected_y1);
        }
    }
}

void Sphere::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) {
    draw_front(dc1);
    draw_top(dc2);
    draw_side(dc3);
    draw_perspective(dc4);
}
