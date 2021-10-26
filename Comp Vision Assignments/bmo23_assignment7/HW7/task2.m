%Task2
repo_path = 'D:\cs4379c-fall2021-source';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'HW7'])
addpath([repo_path s 'HW7' s 'training_data'])
addpath([repo_path s 'HW7' s 'new_test_data'])

addpath([repo_path s 'Code' s '00_common' s '00_detection'])

load_mnist

this3 = zeros(28, 28); 
counter3 = 1; 
allcentered3 = zeros(784, 1032); 
avg3 = 0; 

for i = 1:number 
    if mnist_labels(i) == 3
       this3 =  mnist_digits(:,:,i);
       this3= this3(:);
       avg3 = mean(this3);
       std3 = std(this3);
       center3 = (this3 - avg3)/std3;
       allcentered3(:,counter3) = center3;
       counter3 = counter3 + 1; 
    end
end

[average3, eigenvectors3, eigenvalues3] = compute_pca(allcentered3);

for i = 1:5
    visualize = reshape(eigenvectors3(i, 1:784),28, []);
    visualize = normalize(visualize);
    visualize = imresize(visualize, 2, "bilinear");
    figure(i); imshow (visualize);
end
