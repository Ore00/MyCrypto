<!DOCTYPE html>
<!--
/* 
 * Copyright (C) 2018 Linda McGraw
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * Created on : Aug 16, 2018, 2:03:40 PM
 */
-->
 <?php
    include_once("includes/config.inc");
 ?>
<html>
    <head>
        <meta charset="UTF-8">
             
        <title>My Crypto Tool</title>
        <link rel="stylesheet" href="css/main.css">
    </head>
    <body>
      <div class="flex-container">   
        <div id="header" class="">
            <div class="row">  <H2>My Crypto Tool</H2> </div>
            
            <form id="frmCrypto" name="frmCrypto" method="post" enctype="multipart/form-data" class="left">
                <input type="hidden" name="MAX_FILE_SIZE" value="5000000">
                Select a file <input id="userFile" name="userFile" type="file"  accept=".txt" class="fileInput" style="color:transparent;" onchange="this.style.color = 'black'"/>
                <input type="radio" id="cryptoType" name="cryptoType" value="encrypt"> Encrypt
                <input type="radio" id="cryptoType" name="cryptoType" value="decrypt" checked="checked"> Decrypt
                 
                &nbsp; &nbsp; &nbsp;&nbsp;
                Key = <input type="text" id="userKey" name="userKey" placeholder="BCDEFGHIJKLMNOPQRSTUVWXYZ" value="ZHIMNEYXWVUTSRQPOLKJGFDCBA" size="37" maxlength="37">
                &nbsp;&nbsp;
                <input type="submit" id="btnCrypto" name="btnCrypto" value="Convert" class="btn" alt="Process input file">
               
            </form>
           <div id="form_status" name="form_status" class="row"></div>    
        </div> 
         
      </div>     
     <div class="flex-container">   
        <div id="left" class="column"></div> 
        
        <div id="right" class="column"></div>
     </div>
    <div class="flex-container">   
        <div id="footer" class="center"></div> 
    </div>    
       
    </body>
    <script src="vendor/jquery.js"></script>
    <script src="js/main.js"></script>
</html>
