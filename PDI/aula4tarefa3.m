pkg load image
A = imread('cameraman.tif');
subplot(1,3,1), imshow(A);


Output = immultiply(A,1.5);
subplot(1,3,2), imshow(Output);
Output = imdivide(A,4);
subplot(1,3,3),imshow(Output);

B = imread('cola1.png');
figure, subplot(1,3,1),imshow(B);

BOutput(:,:,1) = immultiply(B(:,:,1),1.5);
BOutput(:,:,2) = immultiply(B(:,:,2),1.5);
BOutput(:,:,3) = immultiply(B(:,:,3),1.5);

subplot(1,3,2),imshow(BOutput);

BOutput(:,:,1) = imdivide(B(:,:,1),4);
BOutput(:,:,2) = imdivide(B(:,:,2),4);
BOutput(:,:,3) = imdivide(B(:,:,3),4);

subplot(1,3,3),imshow(BOutput);