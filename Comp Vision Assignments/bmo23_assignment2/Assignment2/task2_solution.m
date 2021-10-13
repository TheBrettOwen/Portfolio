filename = 'soccer_field4.jpg';
color = double(imread(filename));

r = color(:,:, 1);
g = color(:,:, 2);
b = color(:,:, 3);

%%
green = ((g - r > 30) & (g - b > 10));
%green = imdilate(green, ones(3,3));
field = remove_holes(green);
figure(1); imshow(field); 

%%
red = ((r - g > 30 ) & (r - b > 30));
red = (red & field);
figure(2); imshow(red);
%% 
blue = ((b - r > 20) & (b - g > 20));
blue = (blue & field);
figure(3); imshow(blue);