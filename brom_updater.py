import os
import glob
import shutil
import zipfile
import uuid


def do_BROM_update(flash_code_dir, brom_release_dir):
    current_dir = os.getcwd()

    local = download_BROM(brom_release_dir)
    print('local temp dir = '+local)

    unzip_BROM_artifacts(local)
    
    copy_BROM_artifacts(local,flash_code_dir)

    os.chdir(current_dir)

    shutil.rmtree(local)
    

############### bellow are all internal functions ################

#copy download brom release to a local temp dir
def download_BROM(dest_dir):
    temp_folder = str(uuid.uuid1())
    base_folder = os.getenv('TEMP')
    
    local_dir = os.path.join(base_folder,temp_folder)
    
    shutil.copytree(dest_dir, local_dir)
    return local_dir


#unzip brom.zip
def unzip_BROM_artifacts(src_dir):
    os.chdir(src_dir)

    package_name = glob.glob("brom*.zip")[0]

    zip_package = zipfile.ZipFile(package_name,'r',zipfile.ZIP_DEFLATED)
    zip_package.extractall()
    zip_package.close()


#  src_dir  = 'C:\Documents and Settings\mtk81019\Desktop\6.1117.01.0'
#  dest_dir = 'D:\codebase\SV3_SV5_Migration_Dev'
#
#  src_dir arch for headers: '\output\include'
#  dest_dir arch for headers: '\BootRom'

def copy_artifacts(src_dir, dest_dir, src_patterns, dest_sub_dirs):
    os.chdir(src_dir)

    for f in glob.glob(src_patterns):
        src_file = os.path.join(src_dir,f)
        
        name = os.path.basename(f)
        dest_file = os.path.join(dest_dir,dest_sub_dirs,name)

        if(os.path.isfile(src_file)):
            print('copying '+src_file+' >> '+dest_file)
            shutil.copy(src_file, dest_file)
            

def copy_headers(src_dir, dest_dir):
    copy_artifacts(src_dir, dest_dir, 'output\\include\\*', 'BootRom')

def copy_dll(src_dir, dest_dir):
    copy_artifacts(src_dir, dest_dir, 'output\\bcb\\Release\\*.dll', 'output')

def copy_lib(src_dir, dest_dir):
    copy_artifacts(src_dir, dest_dir, 'output\\bcb\\Release\\*.lib', 'lib')

def copy_DA(src_dir, dest_dir):
    copy_artifacts(src_dir, dest_dir, 'output\\bin\\*.bin', 'output')

def copy_NandUtil(src_dir, dest_dir):
    copy_artifacts(src_dir, dest_dir, '*.bin', 'output')


def copy_BROM_artifacts(src_dir, dest_dir):
    copy_headers(src_dir, dest_dir)
    copy_dll(src_dir, dest_dir)
    copy_lib(src_dir, dest_dir)
    copy_DA(src_dir, dest_dir)
    copy_NandUtil(src_dir, dest_dir)


    

if __name__ == '__main__':
    dest_dir = os.getcwd()

    if(not os.path.exists(os.path.join(dest_dir,'Flash_tool.bpr'))):
        print('Invalid working dir! It only works under Flash tool dev dir!')
        exit(-1)
    
    print('Please input brom release path: \n')
    brom_dir = input()
    
    if(not os.path.exists(brom_dir)):
        print('Invalid brom path!')
        exit(-1)

    do_BROM_update(dest_dir, brom_dir)

    #srcdir = 'C:\\Documents and Settings\\mtk81019\\Desktop\\6.1117.01.0'
    #desdir = 'D:\\codebase\\SV3_SV5_Migration_Dev'
    #brom_dir = '\\\\glbfs14\\sw_releases\\Wireless_Global_Tools\\Tool_Release\\SP Flash Tool\\For WCP2_OSS1_SS1\\SV3_SV5_Integration\\6.1117.03.0'

    #do_update(desdir,brom_dir)

    #current_dir = os.getcwd()

    #local = download_BROM('\\\\glbfs14\\sw_releases\\Wireless_Global_Tools\\Tool_Release\\SP Flash Tool\\For WCP2_OSS1_SS1\\SV3_SV5_Integration\\6.1117.03.0')
    #print('local temp dir = '+local)

    #unzip_BROM_artifacts(local)
    
    #copy_BROM_artifacts(local,desdir)

    #os.chdir(current_dir)

    #shutil.rmtree(local)

    #copy_artifacts(srcdir, desdir, 'output\\include\\*', 'BootRom')
    
    
    
