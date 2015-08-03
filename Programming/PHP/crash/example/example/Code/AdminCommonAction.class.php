<?php
/**
 * AdminCommonAction.class.php
 * @copyright			copyright(c) 2011 - 2012 极好居
 * @author				anqiu xiao
 * @contact				QQ:89249294 E-mail:jihaoju@qq.com
 * @date				Tue Apr 03 14:56:58 CST 2012
 */
class AdminCommonAction extends CommonAction 
{
    protected function _initialize()
    {
    	parent::_initialize();
    	$m_name = MODULE_NAME;
    	$a_name = ACTION_NAME;
    	//禁止通过URL访问的操作
    	if(in_array($m_name.'.'.strtolower($a_name), C('APP_ACTION_DENY_LIST'))){
    		die('Hacking attempt.');
    	}
    	//无需验证的模块
    	$not_auth_modules = C('NOT_AUTH_MODULES');
    	//无需验证的操作
    	$not_auth_actions = C('NOT_AUTH_ACTIONS');
    	if(! in_array($m_name.'.'.$a_name, C('NOT_LOGIN_ACTIONS'))){
    		$this->_checkLogin();
    	}
    	//权限验证
    	if(! $_SESSION[C('SESSION_PREFIX') . 'is_super'] && $a_name != 'editField' && $a_name != 'toggleStatus'
    		 && ! in_array($m_name, $not_auth_modules) && ! in_array($m_name.'.'.$a_name, $not_auth_actions)){
    	 	//需要超级管理员权限的模块
    	 	$super_prive_modules = array('Admin', 'Cache', 'City', 'Priv', 'Role', 'SearchIndex'
    	 								, 'SysConf', 'TempFile', 'VerifyCode');
    		//验证权限
    		if(in_array($m_name, $super_prive_modules) || ! AdminPriv::checkPrive($m_name, strtolower($a_name))){
    			if(! IS_AJAX){
    				if(isset($_REQUEST['is_iframe']) && $_REQUEST['is_iframe']){
    					exit('<center><strong>您没有权限进行此操作</strong></center>');
    				}else{
    					$this->assign('jumpUrl', $this->_refererUrl);
    					$this->error('您没有权限进行此操作.');
    				}
    			}else{
    				$this->ajaxReturn('','您没有权限进行此操作',0);
    			}
    			exit();
    		}
    	}
    	if(! isset($_SESSION[C('SESSION_PREFIX') . 'user_id'])){
    		$_SESSION[C('SESSION_PREFIX') . 'user_id'] = 0;
    		$_SESSION[C('SESSION_PREFIX') . 'user_name'] = '';
    		$_SESSION[C('SESSION_PREFIX') . 'name'] = '';
    		$_SESSION[C('SESSION_PREFIX') . 'is_super'] = false;
    		$_SESSION[C('SESSION_PREFIX') . 'user_roles'] = array();
    	}
    	
    	if(! IS_AJAX && ! IS_POST){
			$this->assign('copyright', sprintf('%s 版权所有 &copy; 2012-%s  系统版本 <span id="version_tip">v%s</span><span id="office_forum"><a href="http://www.tp-coupon.com" target="_blank">官方论坛</a></span>', 'TP-COUPON', date('Y'), APP_VERSION . ' Release ' . PUBDATE));
		}
	}
	
	public function editField()
	{
		$action = '';
		if(empty($_REQUEST['model'])){
			$action = strtolower(trim($_REQUEST['field']));
		}else{
			$action = $_REQUEST['model'] . '_' .strtolower(trim($_REQUEST['field']));
		}
		if(! AdminPriv::checkPrive(MODULE_NAME, $action)){
			$this->ajaxReturn('','您没有权限进行此操作',0);
		}
		$id = intval($_REQUEST['id']);
		if($id == 0)
			exit;
		
		$val = trim($_REQUEST['val']);
		if($val == '')
			exit;
			
		$field = trim($_REQUEST['field']);
		if(empty($field))
			exit;
		$name = $_REQUEST['model'] ? $_REQUEST['model'] : $this->getActionName();
		if(empty($name))
			exit;
		$model = D($name);
		if(! $model instanceof Model){
			$model = M($name);
			if(! $model instanceof Model){
				exit;
			}
		}
		$pk = $_REQUEST['pk'] ? $_REQUEST['pk'] : $model->getPk();
		
		$data = array();
		//$data[$pk] = $id;
		$data[$field] = $val;
		
		if(false !== $model->where("$pk='$id'")->save($data))
		{
			//清空数据缓存
			clear_all_caches();
			$this->ajaxReturn('',$val,1);
		}
		else
		{
			$this->ajaxReturn('','操作失败',0);
		}
	}
	
	public function toggleStatus()
	{
		$action = '';
		if(empty($_REQUEST['model'])){
			$action = strtolower(trim($_REQUEST['field']));
		}else{
			$action = $_REQUEST['model'] . '_' .strtolower(trim($_REQUEST['field']));
		}
		if(! AdminPriv::checkPrive(MODULE_NAME, $action)){
			$this->ajaxReturn('','您没有权限进行此操作',0);
		}
		$id = intval($_REQUEST['id']);
		if($id == 0)
			exit;
		
		$val = intval($_REQUEST['val']) == 0 ? 1 : 0;
			
		$field = trim($_REQUEST['field']);
		if(empty($field))
			exit;
		$name = $_REQUEST['model'] ? $_REQUEST['model'] : $this->getActionName();
		if(empty($name))
			exit;
		$model = D($name);
		if(! $model instanceof Model){
			$model = M($name);
			if(! $model instanceof Model){
				exit;
			}
		}
		$pk = $_REQUEST['pk'] ? $_REQUEST['pk'] : $model->getPk();
		if(false !== $model->where($pk.' = '.$id)->setField($field,$val))
		{
			//清空数据缓存
			clear_all_caches();
			$this->ajaxReturn('',$val,1);
		}
		else
		{
			$this->ajaxReturn('','操作失败',0);
		}
	}

	private function _checkLogin()
	{
		if(! isset($_SESSION[C('SESSION_PREFIX') . 'user_id']) || ! $_SESSION[C('SESSION_PREFIX') . 'user_id']){
			redirect('?g='.GROUP_NAME.'&m=User&a=login');
		}
	}
}