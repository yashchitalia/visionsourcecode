%TEXTON METHOD FOR QUANTIFYING APPEARANCE VARIATION
close all;clear all;clc;
%initialization of parameters
test_dir = 'test_images';
image_type = 'jpg';
TRAINING = true;
training_dir = 'training_images';
appearance_variation = true;
graphics = true;
output_to_screen = true;
no_textons=30;%there are 30 textons in the dictionary
%Forming the dictionary of codewords
warning off all; % the used jpeg images give some warnings.
training_images = makeListOfFiles(training_dir, image_type);
%loading learned dictionary of textons
load('Dictionary.mat');
% enable the formTextonDictionaryModified function to train from
% training_images dataset
% Dictionary = formTextonDictionaryModified(training_dir, training_images,output_to_screen, graphics);

%Obtaining distributions from the test images
% load test images
test_images = makeListOfFiles(test_dir, image_type);
n_images = length(test_images);
% initialize outputs
n_dims =no_textons;
Distributions = zeros(n_images, n_dims);
Entropies = zeros(n_images,1);
fprintf('Extracting texton distributions from test images.\n');
% extract texton distributions:
h = figure();
for im = 1:n_images
    % load image:
    fprintf('Image %d / %d\n', im, n_images);
    Image = loadImage([test_dir, '/', test_images{im}],1,true);
    % extract distribution:
    distribution = getTextonDistributionFromImage(Image, Dictionary);
    Distributions(im, :) = distribution;
    % calculate entropy:
    Entropies(im) = getEntropy(distribution');
    figure(h);
    subplot(1,2,1);
    imshow(Image);
    title('Image');
    subplot(1,2,2);
    plot(1:im, Entropies(1:im), 'LineWidth', 2, 'Color', 'red');
    title('Entropy over time.');
end
%plotting the smoothened entropy values ('smooth' uses a moving average
%filter)
    figure(h);
    subplot(1,2,2);
    hold on;
    plot(1:n_images, smooth(Entropies(1:n_images)), 'LineWidth', 2, 'Color', 'blue');
    

