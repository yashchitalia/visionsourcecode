function files_of_type = makeListOfFiles(file_dir, file_type)
% makes a list of files in the directory 'file_dir' of all files of a
% certain type.
files = dir(file_dir);
n_files = size(files,1);
files_of_type = cell(n_files,1);
fot = 0;
for f = 3:n_files
    i = findstr(files(f).name, ['.' file_type]);
    if(sum(size(i)) >= 2)
        fot = fot + 1;
        files_of_type{fot} = files(f).name;
    end
end
files_of_type = files_of_type(1:fot);

    
