%Task1 
repo_path = 'D:\cs4379c-fall2021-source';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'HW7'])
addpath([repo_path s 'HW7' s 'training_data'])
addpath([repo_path s 'HW7' s 'new_test_data'])

addpath([repo_path s 'Code' s '00_common' s '00_detection'])

load_mnist

this2 = zeros(28, 28); 
counter2 = 1; 
allCentered2 = zeros(784, 1032); 
avg2 = 0; 

for i = 1:number 
    if mnist_labels(i) == 2
       this2 =  mnist_digits(:,:,i);
       this2= this2(:);
       avg2 = mean(this2);
       std2 = std(this2);
       center2 = (this2 - avg2)/std2;
       allCentered2(:,counter2) = center2;
       counter2 = counter2 + 1; 
    end
end

[average2, eigenvectors2, eigenvalues2] = compute_pca(allCentered2);

for i = 1:5
    visualize = reshape(eigenvectors2(i, 1:784),28, []);
    visualize = normalize(visualize);
    visualize = imresize(visualize, 2, "bilinear");
    figure(i); imshow (visualize);
end
