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



function uploadFile($file, $dir){
  //Loads a copy of a file to the specified directory  
   $newFile = $dir . basename($_FILES[$file]['name']);
 if(move_uploaded_file($_FILES[$file]['tmp_name'], $newFile)){ 
     return TRUE;     
 }else{
     return FALSE;     
 }  
}
function removeFile($file, $dir){
 //Deletes the uploaded file from the specified directory  
    $loadedFile = $dir . basename($_FILES[$file]['name']);
    if(unlink($loadedFile)){
        return TRUE;
    }else{
        return FALSE;
    }   
}
function loadFile($file, $dir, $cryptoType="decrypt"){
    $loadedFile = $dir . basename($_FILES[$file]['name']);    
    $fileHandle = fopen($loadedFile, 'r');
    $str = "";
    global $plainPairs, $Key, $assocPairs;
    if($fileHandle){
        while(false !== ($char = fgetc($fileHandle))){
            //run encryption function
                if($char !== "\n"){
                    if($cryptoType == "decrypt"){
                         $str .= cipher_decrypt($Key, $char, $plainPairs); 
                    }elseif($cryptoType == "encrypt"){
                         $str .= cipher_encrypt($Key, $char, $assocPairs);                             
                    }else{
                         $str .= $char; 
                    }
                }else{
                   $str .= "<br>";
                    
                }
        } 
        fclose($fileHandle);
        return $str;
    }else{
        return "Error: could not open file " . basename($_FILES[$file]['name']);
    }    
}
function createFile($fileName, $data){
   $n = str_replace("<br>", "\n", $data);
  if(file_put_contents($fileName, $n)){      
      return;
  }else{
    return "Error: unable to open file " . $fileName;  
  }  
}
function downloadFile($fileName){
 header("Content-disposition: attachment; filename=$fileName");
 header("Content-type: text/plain");
 readfile($fileName);
}
function cipher_decrypt($cipher = "", $char = "", $cipherPairs = array()){
  //locate the position of the char in the key
  $cipherPos = strpos(strtoupper($cipher), strtoupper($char));  
  //char is digit or alpha
  if(is_numeric($char)){
      // return the cypher -> decrypted number
     $value = $cipherPairs[$cipherPos];
  }else{
     if(ctype_alpha($char)){
         //is [A-Za-z]
         if(ctype_upper($char)){
             // return the cypher -> decrypted char
             $value = $cipherPairs[$cipherPos];
         }else{
             // return the lower case cypher -> decrypted number
             $value = strtolower($cipherPairs[$cipherPos]);
         }
     }else{
          //return anything not alpha or digit
         $value = $char;
     }       
  }
  return $value;
}
function cipher_encrypt($cipher = "", $char = "", $cipherPairs = array()){
    //lookup char position in plain text
    //char's position in the cipher layout POS 0-25 for aphpa & 26 - 35 for digit
    $num = abs(ord($char));
    if(array_key_exists($num, $cipherPairs)){
        $pos = $cipherPairs[$num];          
    }else{
        $pos = "";
    }    
    $cipherArray = str_split($cipher);
    //char is digit or alpha  
    if($pos !== ""){
        // $value = $cipherArray[$pos];
        if(is_numeric($char)){
               //return the cypher -> encrypted number
                $value = $cipherArray[$pos];
            }else{
                if(ctype_alpha($char)){
                    //if alpha determine case
                    if(ctype_upper($char)){
                      // return the upper case cypher -> encrypted number 
                        $value = $cipherArray[$pos];
                    }else{
                     // return the lower case cypher -> encrypted number 
                        $value = strtolower($cipherArray[$pos]);
                    }            
                }else{
                    //return anything not alpha or digit
                    $value = $char;
                }
            }
    }else{ $value = $char;}
    return  $value;
}
function getASCII_to_cipher_Position($cipherlength = 26){ 
 //Cipher Encrypted Character Association by ASCII
 //Upper char [A-Z] start at 65 and map to cipher key position 0-25 for decoding
 //Lower char [a-z] start at 97 and map to cipher key position 0-25 for decoding
 //Digits start at 48 and map to cipher key position 26-35   
    $u = getCipherAssocatePair(65, 0, 26);
    $l = getCipherAssocatePair(97, 0, 26, $u);
    if($cipherlength > 26){
        //includes digits
        $d = getCipherAssocatePair(48, 26, 36, $l);
    }
    if(isset($d)){$cipherPairs = $d;}else{ $cipherPairs = $l;}
    return $cipherPairs;
}
function getCipher_PlainText($cipherLength = 26, $charStart = 65, $numStart = 48){
//Cipher  Key Structure Info: 
//Positions 0 - 25 are reserved for char [A-Z]
//Positions 26 - 36 are reserved for digits [0-9]    
    for($i = 0; $i < 26; $i++){
        $plainText[$i] = chr($charStart);
        $charStart++;
    }
    if($cipherLength > 27){
        for($n = 0; $n < 10; $n++){
           $plainText[$i] = chr($numStart);
            $numStart++;
            $i++;
        }
    }
    return $plainText;
}

function getCipherAssocatePair($ASCII_start, $ciper_start = 0, $ASCII_max = 26, $assocPairs = array()){
    
  for($i= $ciper_start; $i< $ASCII_max; $i++){
      $assocPairs[$ASCII_start] = $i;
      $ASCII_start++;
  }  
  return $assocPairs;
}


function getASCII(){
     $str = "";
    for($i = 0; $i < 132; $i++ ){
        $str .= $i . " = " . chr($i). "<br>";
    }
    return $str;
}

function array_to_string($array){
 //code used for testing
//printed array as string with new line on dashboard    
    $str = "";
    if(is_array($array)){
                foreach($array as $key => $value){
                    $str .= $key . ": " . $value . "<br>";
               }         
         }
    return $str;
}
