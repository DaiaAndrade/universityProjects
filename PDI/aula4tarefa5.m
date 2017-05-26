pkg load image
I = imread('coins.png');

subplot(1,2,1),imshow(I);

subplot(1,2,2),imhist(I);
