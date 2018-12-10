<?php

/* 
 * Copyright (C) 2018 Linda McGraw
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
Try{
header('Content-Type: application/json; charset="utf-8"');    
include_once("config.inc");
include_once("functions.inc");
if($_POST) {
    $str = "";
    //set user cipher     
   $Key = trim($_POST['userKey']);
  // $KeyArray = str_split($Key);
   //set user action encrypt or decrypt
   $userAction = trim($_POST['cryptoType']);
   $KeyLength = strlen($Key);
   $fileName = $_FILES['userFile']['name'];
   $fileSize = $_FILES['userFile']['size'];
   $fileError = $_FILES['userFile']['error'];
   $fileErrorMsg = array( 0 => 'No error', 1 => 'Upload file exceeds the upload_max_file_size in php.ini', 2 =>'The upload file exceeds the MAX_FILE_SIZE specified in the HTML form', 3 => 'The uploaded file was partially uploaded', 4 => 'No file was loaded', 5 => 'Error not specified', 6 =>'Missing a temporary folder', 7 => 'Failed to write file to disk', 8 => 'A PHP extension stopped the file upload.');
   
   //Declaring globals
    $assocPairs = getASCII_to_cipher_Position($KeyLength); 
    // put the user key to associate with the original [A-Z]chars and [0-9] when key leghth is greater than 26
    $plainPairs = getCipher_PlainText($KeyLength, 65, 48);     

    // prepare output variables
   $originalData = array(); //original text 
   $convertedData = ""; //converted text 
   $error = ""; //process errors

   //check for file Error prior to running upload function
   if($fileError == 0){
    $uploadStatus = uploadFile('userFile', "../uploads/");
        if($uploadStatus == 1){
            $filePath = "../uploads/" . $fileName;
           $originalData = explode("\n",file_get_contents($filePath, FILE_USE_INCLUDE_PATH));    
            $convertedData = loadFile('userFile', "../uploads/", $userAction);           
        }else{
            $data = "Error: problem with file upload";
        }
         //remove imported file
            if(!removeFile('userFile', "../uploads/")){
                $error = "Error: problem removing file " . $fileName;
            }
         //download converted text to a file
            $newFile ="../downloads/plain.txt";
            createFile($newFile, $convertedData);
           // downloadFile($newFile);   
     }else{
             $error = "Error : The system genearated error: " . $fileErrorMsg[$fileError] . ". The file " . $fileName . " wasn't loaded.";
     } 
    //print values 
    echo json_encode([
       'origData' => $originalData,
       'convData' => $convertedData,
       'err' => $error,
    ]);  
    
            
}//End Post

}catch(Exception $e){
    $errMessage = "Error: " . $e->getMessage();
    echo $errMessage;
}
