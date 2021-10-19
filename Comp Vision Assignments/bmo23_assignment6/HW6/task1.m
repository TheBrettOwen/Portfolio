%task1
% Replace this path with your cs4379c-fall2021 git repository path in your system.
repo_path = 'D:\cs4379c-fall2021-source';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'HW6'])
addpath([repo_path s 'HW6' s 'test_data'])

addpath([repo_path s 'Code' s '00_common' s '00_detection'])
addpath([repo_path s 'Code' s '00_common' s '00_images'])
addpath([repo_path s 'Code' s '00_common' s '00_utilities'])
addpath([repo_path s 'Code' s '09_templates'])
addpath([repo_path s 'Data' s '09_templates' s 'frgc2_b'])
cd([repo_path s 'Data' s '09_templates'])

load_mnist

average2 = zeros(28, 28); 
average3 = zeros(28, 28); 
counter2 = 0; 
counter3 = 0; 

%number is the size of the array which is created when load_mnist is called
for i = 1:number 
    if mnist_labels(i) == 2
       average2 = average2 + mnist_digits(:,:,i);
       counter2 = counter2 + 1; 
    end
    if mnist_labels(i) == 3
       average3 = average3 + mnist_digits(:,:,i);
       counter3 = counter3 + 1; 
    end
end
average2 = average2/counter2; 
average3 = average3/counter3;


%keeps the average image looking less like a blob
average2 = normalize(average2);
average3 = normalize(average3);

%gets rid of missing values
average2 = rmmissing(average2,2);
average3 = rmmissing(average3,2);

figure(1); imshow(average2); 
figure(2); imshow(average3);
