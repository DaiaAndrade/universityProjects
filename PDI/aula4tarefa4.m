pkg load image
A = imread('toycars1.png');
B = imread('toycars2.png');

Abw = im2bw(A);
Bbw = im2bw(B);

subplot(1,3,1),imshow(Abw);
subplot(1,3,2),imshow(Bbw);

Output = xor(Abw,Bbw);
subplot(1,3,3),imshow(Output);