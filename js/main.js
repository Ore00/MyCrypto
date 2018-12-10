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

$(document).ready(function() {	
  $('#frmCrypto').submit(function(e){  
    e.preventDefault();
    document.getElementById("form_status").innerHTML = "";
    $("#form_status").removeClass("alert");
       $("#btnCrypto").attr('disable',true); 
       var dataReminder = new FormData(this);    
       var currentFile = document.getElementById("userFile").value;
       var currentKey =  document.getElementById("userKey").value;
       if(currentKey == ""){
          var err = "Enter a key.";
          $("#form_status").addClass("alert");
          document.getElementById("form_status").innerHTML = "<br>" + err + "<br>";
          return;
       }
       if(currentKey.length !== 26 && currentKey.length !== 36){
            if(currentKey.length < 26){
            var err = "Enter an alpha key at least 26 characters, that includes each letter of the alphabet. Example: ZHIMNEYXWVUTSRQPOLKJGFDCBA";
              }
            if(currentKey.length > 26){
                var err = "Enter an alphanumeric key at least 36 characters, the first 26 characters should include each letter of the alphabet.";
                err = err + " The last 10 characters should include each digit 0 thru 9.";
                err = err + "<br>Example: ZHIMNEYXWVUTSRQPOLKJGFDCBA9872106543";
              }
            $("#form_status").addClass("alert");
            document.getElementById("form_status").innerHTML = "<br>" + err + "<br>";
            return;
       }
       
       if(currentFile === ""){
        var err = "Select a text file to begin."; 
        $("#form_status").addClass("alert");
        document.getElementById("form_status").innerHTML = "<br>" + err + "<br>";        
        return;
       }
       //process form    
       var fileType = currentFile.split(".");       
       if(fileType[1].toLowerCase() === "txt"){
           
            $.ajax({
                        url: 'includes/getFile.php',
                        type: 'POST',                       
                        data: dataReminder,
                        contentType: false,
                        processData: false          
            }).done(function(data){ 
           
        //print the original text to the Left Panel
                           if(Array.isArray(data.origData)){
                               var str = "<H3>Original Text</H3><br>";
                               data.origData.forEach(function(element){
                                   str = str + element + "<br>";
                               });                             
                               document.getElementById("left").innerHTML = str;
                          }else{                             
                               document.getElementById("left").innerHTML = "<H3>Original Text</H3><br>" + data.origData;
                          }
                          //print the converted text to the Left Panel
                          if(Array.isArray(data.convData)){
                               var str = "<H3>Converted Text</H3><br>";
                               data.convData.forEach(function(element){
                                   str = str + element + "<br>";
                               });                             
                               document.getElementById("right").innerHTML = str;
                          }else{                             
                               document.getElementById("right").innerHTML = "<H3>Converted Text</H3><br>" + data.convData;
                          }
                        
                    if(data.err !== ""){
                        $("#form_status").addClass("alert");
                              $('#form_status').fadeOut('slow', function(){
                                   $('#form_status').fadeIn('slow').html("<br>" + data.err + "<br>");
                              });
                         }else{    
                            $("#form_status").addClass("sucess");
                             var download = "<br><a href='downloads/plain.txt' target='_blank'>Download</a>";
                             document.getElementById("form_status").innerHTML = download;
                        }    
                        $("#btnCrypto").attr('disable',false);                           
               
            }).fail(function(jqXHR, textStatus){                     
                       $("#btnCrypto").attr('disable',false);
                        $("#form_status").addClass("alert");
                        var err = jqXHR.statusText;                        
                        document.getElementById("form_status").innerHTML = "<br>Error: " + err + "<br>";
            }).always(function(){   
                       $('#form_status')[0].scrollIntoView(); 
 });
       }else{
             var err = "The file must be a text file";
             document.getElementById("left").innerHTML = "<br>" + err + "<br>";
             document.getElementById("right").innerHTML = "";
       }
   });   
  
});
