<?php
/**
 *
 * Sahana Ajax library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage form 
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function create_ajax_call()
{
    echo '<script>';
    echo 'var xmlHttp

function get_data(str,print_element,set_url,hidden)
{
		
if (str.length==0)
  {
  		
  document.getElementById(print_element).innerHTML="";
  return;
  }
xmlHttp=GetXmlHttpObject()
if (xmlHttp==null)
  {
  alert ("Your browser does not support AJAX!");
  return;
  }
var url=set_url;
		if(hidden!="NULL"){
		hidden_input=document.getElementById(hidden).value
		}
			else
				{
					hidden_input="NULL"
				}				
url=set_url+"&input="+str+"&print="+print_element+"&parent_id="+hidden_input;
	//alert(url)
url=url+"&sid="+Math.random();
			
xmlHttp.onreadystatechange=stateChanged;
xmlHttp.open("GET",url,true);
xmlHttp.send(null);
		
}
function stateChanged()
{
	
if (xmlHttp.readyState==4)
{
		
	value=xmlHttp.responseText.split(\':\')	
			
		splited_value=value[1].split(\';\')
				
		if(splited_value==""){
			splited_value[1]=""
			splited_value[0]=""		
		}
	def_display="--select--";			
	def_value=\'<div id="def" onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch\'+value[0]+\'(this.innerHTML,this.id);" class="suggest_link">\'+def_display+\'</div>\'
		
	new_value=def_value+\'<div id=\'+splited_value[0]+\' onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch\'+value[0]+\'(this.innerHTML,this.id);" class="suggest_link">\'+splited_value[1]+\'</div>\'
	
			j=1
			
			for(i=2;i<value.length;i++){
					
			splited_value=value[i].split(\';\')
				
	old_value=\'<div id=\'+splited_value[j-1]+\' onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch\'+value[0]+\'(this.innerHTML,this.id);" class="suggest_link">\'+splited_value[j]+\'</div>\'		
	new_value=new_value+old_value
		j+2	
	}
					
document.getElementById(value[0]).innerHTML=new_value;
		
}
}';
    echo '</script>';

}

function create_suggest($input_element,$print_element)
{
	
    echo '<script>';
    echo '//Mouse over function
function suggestOver(div_value) {
	div_value.className = \'suggest_link_over\';
}
//Mouse out function
function suggestOut(div_value) {
	div_value.className = \'suggest_link\';
	
}';

    echo '</script>';
}

function set_common_styles(){
	echo '<style type="text/css" media="screen">';
    echo 'body1 {
    font: 11px arial;
			}
			.suggest_link {
				background-color:#FFF424;
				padding: 2px 6px 2px 6px;
				
			}
			.suggest_link_over {
				background-color: #DAD11F;
				padding: 2px 6px 2px 6px;
				cursor:pointer;
				
			}';
			
    echo '</style>';
}

function create_xml_http_object(){
	echo '<script>';
	echo 'function GetXmlHttpObject()
{
var xmlHttp=null;
try
  {
  // Firefox, Opera 8.0+, Safari
  xmlHttp=new XMLHttpRequest();
  }
catch (e)
  {
  // Internet Explorer
  try
    {
    xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
    }
  catch (e)
    {
    xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
  }
return xmlHttp;
}
  ';
    echo '</script>';
	
}

function set_result_to_element($input_element,$print_element,$hidden,$reset){
	
	echo '<script>';
	echo 'function setSearch'.$print_element.'(value,id) {
		
			
	document.getElementById(\''.$print_element.'\').innerHTML = \'\';';
			
if(null!=$reset){
	echo 'if(document.getElementById(\'text'.$input_element.'\').value!=value){';
foreach($reset as $rs){
	echo '';
	echo 'document.getElementById(\'text'.$rs.'\').value= \'\';';
	echo 'document.getElementById(\''.$rs.'\').value= \'\';';
	
}
echo '}';
}
echo 'document.getElementById(\'text'.$input_element.'\').value = value;
	  document.getElementById(\''.$hidden.'\').value = id;
';

echo '}';

	echo '</script>';
}

function set_div_styles($print_element){
	
    echo '<style type="text/css" media="screen">';
    echo '#'.$print_element.' {
				z-index: 100; 
				position:absolute; 
				background-color: #CCCCCC;
						
			    display:inline;
				color:#000000;
				text-align: left; 
				font-weight: bold;
				
}';
    echo '</style>';
}
function hide_popup($print_element){
	echo '<script>';
	echo 'window.onclick=test;';
	echo 'function test(){';
		foreach($print_element as $ele){
		echo 'document.getElementById(\''.$ele.'\').innerHTML = \'\';';
		}
	echo '}';
	echo '</script>';
}


function shn_ajax_add_suggest($input_element,$print_element,$hidden,$reset=null){
	
    create_suggest($input_element,$print_element); 
    
    set_result_to_element($input_element,$print_element,$hidden,$reset); 
    set_div_styles($print_element);
}
function shn_ajax_initiate_request(){
	create_xml_http_object();
	create_ajax_call(); 
	set_common_styles();
}
function shn_ajax_text_look_up($label,$name,$hint=null,$url,$value=null,$flag,$extra_opts=null){
    global $global;
    if(NULL==$hint){
        $hint=array('hint');
    }
    if($global["initiate_ajax"]==false){
	    shn_ajax_initiate_request();
	    $global["initiate_ajax"]=true;
    }

	hide_popup($hint);
    for($index=0;$index<count($name);$index++){
	    if(true==$flag){
            if(0==$index){
		        $reset=array_slice($name,1);	
		        shn_ajax_add_suggest($name[0],$hint[0],$name[0],$reset);
		        $extra_opts['value']=$value[0];
		        shn_form_text($label[0],'text'.$name[0],"size=\"30\" autocomplete=off  onclick=\"get_data('*','".$hint[0]."','".$url."','NULL')\" onkeyup=\"get_data(this.value,'".$hint[0]."','".$url."','NULL')\"" ,$extra_opts);
                $extra_opts['help']=null;
		        echo "<div id='".$hint[0]."' style='left: 442px'></div>";
		        ?>
                <input type="hidden" id="<?=$name[0]?>" name="<?=$name[0]?>"  value= />
	
	            <?php
		        }
		        else
		        {
	//$url=$url.'&parent_id=2';//=document.getElementById(\'hidden_'.$name[$index-1].'\').value';
                    $reset=array_slice($name,$index+1);
                    shn_ajax_add_suggest($name[$index],$hint[$index],$name[$index],$reset);
                    $extra_opts['value']=$value[$index];
                    shn_form_text($label[$index],'text'.$name[$index],"size=\"30\" autocomplete=off onclick=\"get_data('*','".$hint[$index]."','".$url."','".$name[$index-1]."')\" onkeyup=\"get_data(this.value,'".$hint[$index]."','".$url."','".$name[$index-1]."')\"" ,$extra_opts);

                    echo "<div id='".$hint[$index]."' style='left: 442px'></div>";
                    ?>
                    <input type="hidden" id="<?=$name[$index]?>" name="<?=$name[$index]?>"  value= />
	
	                <?php
		        }
        }
		else{
			$reset=array_slice($name,$index+1);
            shn_ajax_add_suggest($name[$index],$hint[$index],$name[$index],$reset);
            $extra_opts['value']=$value[$index];
            shn_form_text($label[$index],'text'.$name[$index],"size=\"30\" autocomplete=off onclick=\"get_data('*','".$hint[$index]."','".$url."','".($name[$index]-1)."')\" onkeyup=\"get_data(this.value,'".$hint[$index]."','".$url."','".$name[$index-1]."')\"" ,$extra_opts);

            echo "<div id='".$hint[$index]."' style='left: 442px'></div>";
            ?>
            <input type="hidden" id="<?=$name[$index]?>" name="<?=$name[$index]?>"  value= />
	
	<?php
		}
	}

}


?>