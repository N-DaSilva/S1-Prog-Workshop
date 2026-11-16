#include <sil/sil.hpp>

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
            image.pixel(x, y).r = 0.003 * x;
            image.pixel(x, y).g = 0.003 * x;
            image.pixel(x, y).b = 0.003 * x;
        }
    }
}

void mirror(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width()/2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 temp_color = image.pixel(x,y);
            image.pixel(x, y) = image.pixel(image.width() - 1 - x, y);
            image.pixel(image.width() - 1 - x, y) = temp_color;
        }
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
    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }
}