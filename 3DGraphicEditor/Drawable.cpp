#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"

std::vector<Drawable*> Drawable::figures;
wxColour Drawable::line_color = wxColour(0, 0, 0);;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
double Drawable::panelHeight = 200.0;
double Drawable::panelWidth = 200.0;
int Drawable::highlight_duration_ms = 1000;
double Drawable::highlight_factor = 0.6;

// Camera initializers
double Drawable::Camera::frontDistance = 1.0;
double Drawable::Camera::topDistance = 1.0;
double Drawable::Camera::rightDistance = 1.0;
Position Drawable::Camera::cameraPosition = Position(200, 200, 200);
Position Drawable::Camera::lookAtPosition = Position(0, 0, 0);
double Drawable::Camera::fieldOfView = 60.0;
Position Drawable::Camera::cameraDirection = {
			lookAtPosition.x - cameraPosition.x,
			lookAtPosition.y - cameraPosition.y,
			lookAtPosition.z - cameraPosition.z
};
Position Drawable::Camera::rightVector = {
			cameraDirection.y * 0 - cameraDirection.z * 1,
			cameraDirection.z * 0 - cameraDirection.x * 0,
			cameraDirection.x * 1 - cameraDirection.y * 0
};
Position Drawable::Camera::upVector = {
			rightVector.y * cameraDirection.z - rightVector.z * cameraDirection.y,
			rightVector.z * cameraDirection.x - rightVector.x * cameraDirection.z,
			rightVector.x * cameraDirection.y - rightVector.y * cameraDirection.x
};
const double Drawable::Camera::nearPlane = 0.01; // Distance to near clipping plane
const double Drawable::Camera::farPlane = 100.0; // Distance to far clipping plane
double Drawable::Camera::fovInRadians = fieldOfView * (M_PI / 180.0);
double Drawable::Camera::tanFov = tan(fovInRadians / 2.0);
double Drawable::Camera::aspectRatio = panelWidth / panelHeight;

void Drawable::addObj(Drawable* fig) {
	figures.push_back(fig);
}

void Drawable::deleteObj(int index) {
	if (index >= 1 && index <= figures.size())
		figures.erase(figures.begin() + index - 1);
}

void Drawable::clearAll() {
	for (auto&& fig : figures) delete fig;
	figures.clear();
}

void Drawable::moveObj(int index, double x_shift, double y_shift, double z_shift) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		figures[index - 1]->move(x_shift, y_shift, z_shift);
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		figures[index - 1]->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
}

void Drawable::touchObj(int index) {
	if (index >= 1 && index <= figures.size())
	{
		// Use zero-based indexing internally, so adjust index by -1
		figures[index - 1]->highlightObject();
	}
}

void Drawable::DrawAll(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) {
	for (Drawable* figure : figures)
	{
		figure->draw(dc1, dc2, dc3, dc4);
	}
}

Drawable* Drawable::getObj(int index) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		return figures[index - 1];
	return nullptr;
}

std::vector<Drawable*> Drawable::getAllObjs() {
	return figures;
}

void Drawable::SetLineColor(const wxColour& newColour) {
	line_color = newColour;
}

void Drawable::SetViewSize(const double x, const double y) {
	panelWidth = x;
	panelHeight = y;
}

void Drawable::setColor(const wxColour& newColor) {
	_color = newColor;
}

std::vector<std::vector<double>> Drawable::multiplyMatrix(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
	int rows1 = a.size();
	int cols1 = a[0].size();
	int cols2 = b[0].size();

	std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0));

	for (int i = 0; i < rows1; ++i) {
		for (int j = 0; j < cols2; ++j) {
			for (int k = 0; k < cols1; ++k) {
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return result;
}

std::vector<std::vector<double>> Drawable::generate_rotation_matrix(double alpha, double beta, double gamma)
{
	// Convert angles to radians
	double alphaRadian = alpha * M_PI / 180.0;
	double betaRadian = beta * M_PI / 180.0;
	double gammaRadian = gamma * M_PI / 180.0;

	// Precalculate trigonometric values
	double cosAlpha = cos(alphaRadian);
	double sinAlpha = sin(alphaRadian);
	double cosBeta = cos(betaRadian);
	double sinBeta = sin(betaRadian);
	double cosGamma = cos(gammaRadian);
	double sinGamma = sin(gammaRadian);

	// Create rotation matrices
	std::vector<std::vector<double>> alphaRotation = {
		{1, 0, 0},
		{0, cosAlpha, -sinAlpha},
		{0, sinAlpha, cosAlpha}
	};
	std::vector<std::vector<double>> betaRotation = {
		{cosBeta, 0, sinBeta},
		{0, 1, 0},
		{-sinBeta, 0, cosBeta}
	};
	std::vector<std::vector<double>> gammaRotation = {
		{cosGamma, -sinGamma, 0},
		{sinGamma, cosGamma, 0},
		{0, 0, 1}
	};

	return multiplyMatrix(multiplyMatrix(gammaRotation, betaRotation), alphaRotation);
}

void Drawable::saveToFile(const std::string& fileName)
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file for writing: " << fileName << std::endl;
		return;
	}

	std::ostringstream oss;

	// saving drawable settings
	oss << line_color.GetRGB() << " ";
	oss << fill_style << " ";
	oss << fill_color.GetRGB() << " ";
	oss << std::to_string(static_cast<int>(view_style)) << " ";

	oss << Camera::getFrontDistance() << " ";
	oss << Camera::getTopDistance() << " ";
	oss << Camera::getRightDistance() << " ";

	oss << Camera::getPosition().x << " " << Camera::getPosition().y << " " << Camera::getPosition().z << " ";
	oss << Camera::getLookAt().x << " " << Camera::getLookAt().y << " " << Camera::getLookAt().z << " ";

	oss << Camera::getFov() << "\n";

	for (Drawable* obj : figures)
		oss << obj->save();

	// Output the string stream to the file
	outFile << oss.str();

	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error: Could not properly close the file: " << fileName << std::endl;
	}
}

void Drawable::loadFromFile(const std::string& fileName)
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open file for reading: " << fileName << std::endl;
		return;
	}
	clearAll();  // Clear existing objects before loading new ones

	// loading drawable settings
	std::string line;
	if (std::getline(inFile, line))
	{
		std::istringstream iss(line);

		wxUint32 penColor;
		if (!(iss >> penColor)) {
			std::cerr << "Error: Failed to read pen color." << std::endl;
			return;
		}
		line_color = penColor;

		bool fillStyle;
		wxUint32 fillColor;
		if (!(iss >> fillStyle >> fillColor)) {
			std::cerr << "Error: Failed to read fill settings." << std::endl;
			return;
		}
		fill_style = fillStyle;
		fill_color = fillColor;

		int newView;
		if (!(iss >> newView)) {
			std::cerr << "Error: Failed to read view style." << std::endl;
			return;
		}
		view_style = static_cast<view>(newView);

		double fdist, tdist, rdist;
		if (!(iss >> fdist >> tdist >> rdist)) {
			std::cerr << "Error: Failed to read camera distances." << std::endl;
			return;
		}
		Camera::setFrontDistance(fdist);
		Camera::setTopDistance(tdist);
		Camera::setRightDistance(rdist);

		double posX, posY, posZ;
		if (!(iss >> posX >> posY >> posZ)) {
			std::cerr << "Error: Failed to read camera position." << std::endl;
			return;
		}
		Camera::setPosition(posX, posY, posZ);

		double lookX, lookY, lookZ;
		if (!(iss >> lookX >> lookY >> lookZ)) {
			std::cerr << "Error: Failed to read camera look direction." << std::endl;
			return;
		}
		Camera::setLookAt(lookX, lookY, lookZ);

		double fov;
		if (!(iss >> fov)) {
			std::cerr << "Error: Failed to read camera FOV." << std::endl;
			return;
		}
		Camera::setFov(fov);
	}
	else {
		std::cerr << "Error: Could not read the line from the file." << std::endl;
		return;
	}

	wxUint32 color;
	while (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "Line")
		{
			double x1, y1, z1, x2, y2, z2;
			if (iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> color)
			{
				addObj(new Line(Position(x1, y1, z1), Position(x2, y2, z2), color));
			}
		}
		else if (type == "Sphere")
		{
			double x, y, z, radius;
			int meridians, parallels;
			if (iss >> x >> y >> z >> radius >> meridians >> parallels >> color) {
				addObj(new Sphere(Position(x, y, z), radius, meridians, parallels, color));
			}
		}
		else if (type == "Box")
		{
			double x1, y1, z1, x2, y2, z2;
			if (iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> color)
			{
				addObj(new Box(Position(x1, y1, z1), Position(x2, y2, z2), color));
			}
		}
		else
		{
			std::cerr << "Error: Wrong object type. " << fileName << std::endl;
			return;
		}
		// Add more cases for other Drawable types
	}

	inFile.close();
	if (inFile.fail()) {
		std::cerr << "Error: Could not properly close the file: " << fileName << std::endl;
	}
}

void Drawable::highlightObject()
{
	if (!_highlightTimer)
	{
		wxColour colorBeforeHighlight = _color;

		_color = generateHighlight();

		_highlightTimer = new wxTimer();
		_highlightTimer->StartOnce(Drawable::highlight_duration_ms);

		// Bind the timer event
		_highlightTimer->Bind(wxEVT_TIMER, [this, colorBeforeHighlight](wxTimerEvent& event) {
			ResetHighlight(event, colorBeforeHighlight);
			});
	}
}

const wxColour Drawable::generateHighlight() const {
	return wxColour(
		std::min(_color.GetRed() - highlight_factor * 255, 255.0),
		std::min(_color.GetGreen() - highlight_factor * 255, 255.0),
		std::min(_color.GetBlue() - highlight_factor * 255, 255.0)
	);
};

void  Drawable::ResetHighlight(wxTimerEvent& event, wxColour prev)
{
	_color = prev;
	_highlightTimer->Stop(); // Stop the timer
	delete _highlightTimer; // Clean up the timer object
	_highlightTimer = nullptr;
}

void Drawable::Camera::update() {
	fovInRadians = fieldOfView * (M_PI / 180.0);
	tanFov = tan(fovInRadians / 2.0);
	aspectRatio = panelWidth / panelHeight;

	cameraDirection = {
		lookAtPosition.x - cameraPosition.x,
		lookAtPosition.y - cameraPosition.y,
		lookAtPosition.z - cameraPosition.z
	};
	// Normalize camera direction
	double length = sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.y * cameraDirection.y + cameraDirection.z * cameraDirection.z);
	cameraDirection.x /= length;
	cameraDirection.y /= length;
	cameraDirection.z /= length;

	rightVector = {
		cameraDirection.y * 0 - cameraDirection.z * 1,
		cameraDirection.z * 0 - cameraDirection.x * 0,
		cameraDirection.x * 1 - cameraDirection.y * 0
	};
	// Normalize right vector
	length = sqrt(rightVector.x * rightVector.x + rightVector.y * rightVector.y + rightVector.z * rightVector.z);
	rightVector.x /= length;
	rightVector.y /= length;
	rightVector.z /= length;

	upVector = {
		rightVector.y * cameraDirection.z - rightVector.z * cameraDirection.y,
		rightVector.z * cameraDirection.x - rightVector.x * cameraDirection.z,
		rightVector.x * cameraDirection.y - rightVector.y * cameraDirection.x
	};
}

wxPoint Drawable::Camera::projectPerspective(const Position& pos) {
	// Transform the point to camera space
	double px = pos.x - cameraPosition.x;
	double py = pos.y - cameraPosition.y;
	double pz = pos.z - cameraPosition.z;

	// Apply rotation (camera orientation)
	double camX = px * rightVector.x + py * rightVector.y + pz * rightVector.z;
	double camY = px * upVector.x + py * upVector.y + pz * upVector.z;
	double camZ = px * cameraDirection.x + py * cameraDirection.y + pz * cameraDirection.z;

	// Ensure camZ is not too close to zero to prevent division by zero
	if (camZ < nearPlane) {
		camZ = nearPlane;
	}

	// Perspective projection
	double screenX = (camX / (camZ * tanFov * aspectRatio)) * (panelWidth / 2) + (panelWidth / 2);
	double screenY = (camY / (camZ * tanFov)) * (panelHeight / 2) + (panelHeight / 2);

	return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
}