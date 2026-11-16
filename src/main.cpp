#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>

void keep_green_only(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void channels_swap(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        float temp = color.r;
        color.r = color.b;
        color.b = temp;
    }
}

void black_and_white(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        float luminance = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
        color.r = luminance;
        color.g = luminance;
        color.b = luminance;
    }
}

void negative(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
}

void gradient(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = (1.f / static_cast<float>(image.width())) * x;
            image.pixel(x, y).g = (1.f / static_cast<float>(image.width())) * x;
            image.pixel(x, y).b = (1.f / static_cast<float>(image.width())) * x;
        }
    }
}

void mirror(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 temp_color = image.pixel(x, y);
            image.pixel(x, y) = image.pixel(image.width() - 1 - x, y);
            image.pixel(image.width() - 1 - x, y) = temp_color;
        }
    }
}

void noise(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        if (true_with_probability(0.15))
        {
            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);
        }
    }
}

sil::Image turn_90_deg(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image new_image{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(new_image.width() - 1 - y, x) = image.pixel(x, y);
        }
    }

    return new_image;
}

sil::Image rgb_split(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image new_image{image.width(), image.height()};

    const int gap = 15;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(x, y).r = x >= gap ? image.pixel(x - gap, y).r : 0.f;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(x, y).b = x <= image.width() - 1 - gap ? image.pixel(x + gap, y).r : 0.f;
        }
    }

    return new_image;
}

void lighten(sil::Image &image)
{
    const float power = 0.5;

    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, power);
        color.g = pow(color.g, power);
        color.b = pow(color.b, power);
    }
}

void darken(sil::Image &image)
{
    const float power = 3;

    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, power);
        color.g = pow(color.g, power);
        color.b = pow(color.b, power);
    }
}

int main()
{
    // {
    //     sil::Image image{"images/logo.png"};      // Lis l'image
    //     keep_green_only(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/keep_green_only.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     channels_swap(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/channels_swap.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     black_and_white(image);
    //     image.save("output/black_and_white.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negative(image);
    //     image.save("output/negative.png");
    // }
    // {
    //     sil::Image image{300 /*width*/, 200 /*height*/};
    //     gradient(image);
    //     image.save("output/gradient.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mirror(image);
    //     image.save("output/mirror.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     noise(image);
    //     image.save("output/noise.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     turn_90_deg(image).save("output/90deg.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rgb_split(image).save("output/rgb_split.png");
    // }
    {
        sil::Image image{"images/photo.jpg"};
        lighten(image);
        image.save("output/lighten.png");
        darken(image);
        image.save("output/darken.png");
    }
}