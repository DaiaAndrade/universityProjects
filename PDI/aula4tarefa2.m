pkg load image
A = imread('cola1.png');
B = imread('cola2.png');

subplot(4,2,1),imshow(A);
subplot(4,2,2),imshow(B);

Output = imsubtract(A,B);

subplot(4,2,3),imshow(Output);

Output = imabsdiff(A,B);
subplot(4,2,4),imshow(Output);

Outro1 = rgb2gray(A);
subplot(4,2,5),imshow(Outro1);
Outro2 = rgb2gray(B);
subplot(4,2,6),imshow(Outro2);

Output = imsubtract(Outro1,Outro2);
subplot(4,2,7),imshow(Output);

Output = imabsdiff(Outro1,Outro2);
subplot(4,2,8),imshow(Output);